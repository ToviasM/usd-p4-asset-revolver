#include "resolverContext.h"

#include "pxr/pxr.h"
#include "pxr/base/tf/pyUtils.h"
#include "pxr/usd/ar/pyResolverContext.h"

#include "boost_include_wrapper.h"
#include BOOST_INCLUDE(python/class.hpp)
#include BOOST_INCLUDE(python/operators.hpp)
#include BOOST_INCLUDE(python/return_value_policy.hpp)

#include <string>

using namespace AR_BOOST_NAMESPACE::python;

PXR_NAMESPACE_USING_DIRECTIVE

static
size_t
_Hash(const PerforceResolverContext& ctx)
{
    return hash_value(ctx);
}

static
std::string
_Repr(const PerforceResolverContext& ctx)
{
    return TF_PY_REPR_PREFIX + "ResolverContext";
}

void
wrapResolverContext()
{
    using This = PerforceResolverContext;

    class_<PerforceResolverContext>("ResolverContext", no_init)
        .def(init<>())
        .def(self == self)
        .def(self != self)
        .def("__hash__", _Hash)
        .def("__repr__", _Repr)
    ;
    ArWrapResolverContextForPython<This>();
}
