
#include "component.h"
using namespace std;

Component::Component(TYPE_NAME tp){ type = tp; }
TYPE_NAME Component::get_type() { return type; }

void Component::set_filter_type(FILTER_TYPE ft) { ftype = ft; }
FILTER_TYPE Component::get_filter_type() { return ftype; }

bool Component::operator<(const Component& cp) const
{
  if(get_value()[0]>='0' && get_value()[0]<='9')
    return stoi(get_value()) < stoi(cp.get_value());
  return get_value() < cp.get_value();
}

bool Component::operator==(const Component& cp) const
{
  return get_value() == cp.get_value();
}
