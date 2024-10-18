#ifndef AR_PERFORCERESOLVER_TOKENS_H
#define AR_PERFORCERESOLVER_TOKENS_H

#include "api.h"

#include <pxr/pxr.h>
#include <pxr/base/tf/staticTokens.h>

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

struct PerforceResolverTokensType
{
    AR_PERFORCERESOLVER_API PerforceResolverTokensType();

    const TfToken mappingPairs;
    const std::vector<TfToken> allTokens;
};

extern AR_PERFORCERESOLVER_API TfStaticData<PerforceResolverTokensType> PerforceResolverTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif // AR_PERFORCERESOLVER_TOKENS_H