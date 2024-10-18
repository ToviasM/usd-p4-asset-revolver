#include "debugCodes.h"

#include <pxr/base/tf/registryManager.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
    TF_DEBUG_ENVIRONMENT_SYMBOL(PERFORCERESOLVER_RESOLVER, "Print debug output during path resolution");
}

PXR_NAMESPACE_CLOSE_SCOPE
