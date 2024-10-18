#ifndef AR_FILERESOLVER_RESOLVER_CONTEXT_H
#define AR_FILERESOLVER_RESOLVER_CONTEXT_H

#include <memory>
#include <regex>
#include <string>
#include <map>

#include "pxr/pxr.h"
#include "pxr/usd/ar/defineResolverContext.h"
#include "pxr/usd/ar/resolverContext.h"

#include "api.h"
#include "debugCodes.h"

class PerforceResolverContext
{
public:
    // Constructors
    AR_PERFORCERESOLVER_API
    PerforceResolverContext();
    AR_PERFORCERESOLVER_API
    PerforceResolverContext(const PerforceResolverContext& ctx);

    // Standard Ops
    AR_PERFORCERESOLVER_API
    bool operator<(const PerforceResolverContext& ctx) const;
    AR_PERFORCERESOLVER_API
    bool operator==(const PerforceResolverContext& ctx) const;
    AR_PERFORCERESOLVER_API
    bool operator!=(const PerforceResolverContext& ctx) const;
    AR_PERFORCERESOLVER_API
    friend size_t hash_value(const PerforceResolverContext& ctx);

};

PXR_NAMESPACE_OPEN_SCOPE
AR_DECLARE_RESOLVER_CONTEXT(PerforceResolverContext);
PXR_NAMESPACE_CLOSE_SCOPE

#endif // AR_FILERESOLVER_RESOLVER_CONTEXT_H