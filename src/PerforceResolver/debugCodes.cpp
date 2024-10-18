#include "debugCodes.h"

#include <pxr/base/tf/registryManager.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
    TF_DEBUG_ENVIRONMENT_SYMBOL(PERFORCE_RESOLVER, "Print debug output during path resolution");
    TF_DEBUG_ENVIRONMENT_SYMBOL(PERFORCE_CLIENT, "Print debug perforce client output during path resolution");
}

PXR_NAMESPACE_CLOSE_SCOPE
