
#include "component.h"
using namespace std;

Component::Component(TYPE_NAME tp){ type = tp; }
TYPE_NAME Component::get_type() { return type; }

bool Component::operator<(const Component& cp) const
{
  cout << "OPERATOR : " << get_value() << " < " << cp.get_value() << endl;
  if(get_value()[0]>='0' && get_value()[0]<='9')
    return stoi(get_value()) < stoi(cp.get_value());
  return get_value() < cp.get_value();
}

bool Component::operator==(const Component& cp) const
{
  return get_value() == cp.get_value();
}
