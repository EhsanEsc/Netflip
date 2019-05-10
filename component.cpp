
#include "component.h"
using namespace std;

Component::Component(TYPE_NAME tp){ type = tp; }
TYPE_NAME Component::get_type() { return type; }
// virtual bool Component::operator<(const Component& cp) const { return true; }
// virtual bool Component::operator==(const Component& cp) const { return true; }
