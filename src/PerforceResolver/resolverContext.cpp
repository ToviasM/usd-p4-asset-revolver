#define CONVERT_STRING(string) #string
#define DEFINE_STRING(string) CONVERT_STRING(string)

#include "resolverContext.h"

#include "pxr/pxr.h"
#include "pxr/base/tf/getenv.h"
#include "pxr/base/tf/pathUtils.h"
#include <pxr/usd/sdf/layer.h>

#include <iostream>
#include <vector>

PXR_NAMESPACE_USING_DIRECTIVE

PerforceResolverContext::PerforceResolverContext() {
}

PerforceResolverContext::PerforceResolverContext(const PerforceResolverContext& ctx) = default;

bool
PerforceResolverContext::operator<(
    const PerforceResolverContext& ctx) const
{
    // This is a no-op for now, as it doesn't get used for now.
    return true;
}

bool
PerforceResolverContext::operator==(
    const PerforceResolverContext& ctx) const
{
    return true;
}

bool
PerforceResolverContext::operator!=(
    const PerforceResolverContext& ctx) const
{
    return true;
}

size_t hash_value(const PerforceResolverContext& ctx)
{
    return TfHash()("test/hash/value");
}