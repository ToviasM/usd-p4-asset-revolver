#ifndef AR_PERFORCERESOLVER_RESOLVER_H
#define AR_PERFORCERESOLVER_RESOLVER_H

#include "api.h"
#include "debugCodes.h"
#include "pxr/pxr.h"
#include "pxr/usd/ar/resolver.h"
#include <pxr/usd/ar/defaultResolver.h>

#include <memory>
#include <string>
#include <map>

PXR_NAMESPACE_OPEN_SCOPE

class PerforceResolver final : public ArResolver
{
public:
    AR_PERFORCERESOLVER_API
    PerforceResolver();

    AR_PERFORCERESOLVER_API
    virtual ~PerforceResolver();

protected:
	AR_PERFORCERESOLVER_API
	virtual std::string _CreateIdentifier(const std::string& assetPath, const ArResolvedPath& anchorAssetPath) const override;

	AR_PERFORCERESOLVER_API
	virtual std::string _CreateIdentifierForNewAsset(const std::string& assetPath, const ArResolvedPath& anchorAssetPath) const override;

    AR_PERFORCERESOLVER_API
        ArResolvedPath _Resolve(
            const std::string& assetPath) const final;

    AR_PERFORCERESOLVER_API
        ArResolvedPath _ResolveForNewAsset(
            const std::string& assetPath) const final;

    AR_PERFORCERESOLVER_API
        ArResolverContext _CreateDefaultContext() const final;

    AR_PERFORCERESOLVER_API
        ArResolverContext _CreateDefaultContextForAsset(
            const std::string& assetPath) const final;

    AR_PERFORCERESOLVER_API
        ArTimestamp _GetModificationTimestamp(
            const std::string& assetPath,
            const ArResolvedPath& resolvedPath) const final;

    AR_PERFORCERESOLVER_API
        std::shared_ptr<ArAsset> _OpenAsset(
            const ArResolvedPath& resolvedPath) const final;

    AR_PERFORCERESOLVER_API
        std::shared_ptr<ArWritableAsset> _OpenAssetForWrite(
            const ArResolvedPath& resolvedPath,
            WriteMode writeMode) const final;
    
private:
    ArDefaultResolver _defaultResolver;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // AR_PERFORCERESOLVER_RESOLVER_H