#pragma once

#include <strix/net/object/_Object.h>
#include <strix/net/object/MetaClassT.h>

namespace strix { namespace net { namespace object {

template <class Class>
bool Object::InstanceOf() const { return InstanceOf(MetaClassT<Class>::Get()); }

} } }
