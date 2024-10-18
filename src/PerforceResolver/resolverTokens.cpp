#include "resolverTokens.h"

PXR_NAMESPACE_OPEN_SCOPE

PerforceResolverTokensType::PerforceResolverTokensType() :
    mappingPairs("mappingPairs", TfToken::Immortal),
    allTokens({
        mappingPairs
    })
{
}

TfStaticData<PerforceResolverTokensType> PerforceResolverTokens;

PXR_NAMESPACE_CLOSE_SCOPE
