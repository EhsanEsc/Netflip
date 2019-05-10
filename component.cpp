
#include "component.h"

Component::Component(TYPE_NAME tp){ type = tp; }
virtual bool Component::operator<(const Component& cp) const { return true; }
virtual bool Component::operator==(const Component& cp) const { return true; }
