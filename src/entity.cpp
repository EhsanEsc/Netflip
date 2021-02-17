
#include "entity.h"
using namespace std;

Entity::Entity(Parametrs cps,Typelist attributes,map<TYPE_NAME,string> attributes_default_value)
{
  valid = true;
  components = cps;
  add_optimal_attribute(attributes, attributes_default_value);
}

void Entity::add_optimal_attribute(Typelist attributes,map<TYPE_NAME,string> attributes_default_value)
{
  for(auto& at:attributes)
  {
    if(get_component_bytype(at) == NULL)
    {
      string value = attributes_default_value[at];
      if(value == "")
      {
        valid = false;
        continue;
      }
      components.push_back(build_component(at,value));
    }
  }
}

Component* Entity::get_component_bytype(TYPE_NAME tn)
{
  for(auto& cp:components)
    if(cp->get_type() == tn)
      return cp;
  return NULL;
}

bool Entity::is_ok() { return valid; }
