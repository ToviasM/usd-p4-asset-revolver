#define CONVERT_STRING(string) #string
#define DEFINE_STRING(string) CONVERT_STRING(string)

#include "resolver.h"
#include "perforceWrapper.h"

#include "pxr/base/arch/systemInfo.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/getenv.h"
#include "pxr/base/tf/pathUtils.h"
#include "pxr/base/tf/pyInvoke.h"
#include "pxr/base/tf/staticTokens.h"
#include "pxr/usd/ar/defineResolver.h"
#include "pxr/usd/ar/filesystemAsset.h"
#include "pxr/usd/ar/filesystemWritableAsset.h"
#include "pxr/usd/ar/notice.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <regex>

PXR_NAMESPACE_OPEN_SCOPE

AR_DEFINE_RESOLVER(PerforceResolver, ArResolver);

static bool
_IsRelativePath(const std::string& path)
{
    return (!path.empty() && TfIsRelativePath(path));
}

static bool
_IsDepotPath(const std::string& path) {
    TF_DEBUG(PERFORCE_RESOLVER, "Checking for depot path!\n");
    return path.find("//") == 0;
}


static std::string
_AnchorRelativePath(
    const std::string& anchorPath, 
    const std::string& path)
{
    if (TfIsRelativePath(anchorPath) ||
        !_IsRelativePath(path)) {
        return path;
    }
    // Ensure we are using forward slashes and not back slashes.
    std::string forwardPath = anchorPath;
    std::replace(forwardPath.begin(), forwardPath.end(), '\\', '/');
    // If anchorPath does not end with a '/', we assume it is specifying
    // a file, strip off the last component, and anchor the path to that
    // directory.
    const std::string anchoredPath = TfStringCatPaths(TfStringGetBeforeSuffix(forwardPath, '/'), path);
    return TfNormPath(anchoredPath);
}

static ArResolvedPath
_ResolveAnchored(
    const std::string& anchorPath,
    const std::string& path)
{
    std::string resolvedPath = path;
    if (!anchorPath.empty()) {
        resolvedPath = TfStringCatPaths(anchorPath, path);
    }
    if (_IsDepotPath(path))
    {
        PerforceClient cli = PerforceClient();
        if (cli.client.Dropped())
        {
            TF_DEBUG(PERFORCE_RESOLVER).Msg("Was unable to connect to server, server was dropped or never connected...\n");
            return ArResolvedPath();
        }
        TF_DEBUG(PERFORCE_RESOLVER, "Syncing Path...\n");
        cli.sync_file(path);
        std::string localAssetPath = cli.get_absolute_path(path);
        return ArResolvedPath(TfNormPath(localAssetPath));

    }
    return TfPathExists(resolvedPath) ? ArResolvedPath(TfAbsPath(resolvedPath)) : ArResolvedPath();
}

PerforceResolver::PerforceResolver() {
    TF_DEBUG(PERFORCE_RESOLVER).Msg("PerforceResolver::PerforceResolver()");
};
    
PerforceResolver::~PerforceResolver() = default;

std::string
PerforceResolver::_CreateIdentifier(
    const std::string& assetPath,
    const ArResolvedPath& anchorAssetPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg("Resolver::_CreateIdentifier('%s', '%s')\n",
        assetPath.c_str(), anchorAssetPath.GetPathString().c_str());

    if (assetPath.empty()) {
        return assetPath;
    }

    if (!anchorAssetPath) {
        return TfNormPath(assetPath);
    }

    const std::string anchoredAssetPath = _AnchorRelativePath(anchorAssetPath, assetPath);

    return TfNormPath(anchoredAssetPath);
}

std::string
PerforceResolver::_CreateIdentifierForNewAsset(
    const std::string& assetPath,
    const ArResolvedPath& anchorAssetPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg(
        "Resolver::_CreateIdentifierForNewAsset"
        "('%s', '%s')\n",
        assetPath.c_str(), anchorAssetPath.GetPathString().c_str());
    if (assetPath.empty()) {
        return assetPath;
    }

    if (_IsRelativePath(assetPath)) {
        return TfNormPath(anchorAssetPath ?
            _AnchorRelativePath(anchorAssetPath, assetPath) :
            TfAbsPath(assetPath));
    }

    return TfNormPath(assetPath);
}

ArResolvedPath
PerforceResolver::_Resolve(const std::string& assetPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg("MultiResolver::_Resolve('%s')\n", assetPath.c_str());

    if (assetPath.empty()) {
        return ArResolvedPath();
    }
    return _ResolveAnchored(std::string(), assetPath);
}

ArResolvedPath
PerforceResolver::_ResolveForNewAsset(const std::string& assetPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg("MultiResolver::_ResolveForNewAsset('%s')\n", assetPath.c_str());
    return ArResolvedPath();
}

ArTimestamp
PerforceResolver::_GetModificationTimestamp(
    const std::string& assetPath,
    const ArResolvedPath& resolvedPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg(
        "Resolver::GetModificationTimestamp('%s', '%s')\n",
        assetPath.c_str(), resolvedPath.GetPathString().c_str());
    return ArFilesystemAsset::GetModificationTimestamp(resolvedPath);
}

std::shared_ptr<ArAsset>
PerforceResolver::_OpenAsset(
    const ArResolvedPath& resolvedPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg(
        "Resolver::OpenAsset('%s')\n",
        resolvedPath.GetPathString().c_str());
    return ArFilesystemAsset::Open(resolvedPath);
}

std::shared_ptr<ArWritableAsset>
PerforceResolver::_OpenAssetForWrite(
    const ArResolvedPath& resolvedPath,
    WriteMode writeMode) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg(
        "Resolver::_OpenAssetForWrite('%s', %d)\n",
        resolvedPath.GetPathString().c_str(),
        static_cast<int>(writeMode));
    return ArFilesystemWritableAsset::Create(resolvedPath, writeMode);
}

ArResolverContext
PerforceResolver::_CreateDefaultContext() const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg("PerforceResolver::_CreateDefaultContext()\n");
    return ArResolverContext();
}

ArResolverContext
PerforceResolver::_CreateDefaultContextForAsset(const std::string& assetPath) const
{
    TF_DEBUG(PERFORCE_RESOLVER).Msg("PerforceResolver::_CreateDefaultContextForAsset()\n");
    return _CreateDefaultContext();
}

PXR_NAMESPACE_CLOSE_SCOPE