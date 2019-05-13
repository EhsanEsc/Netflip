
#include "entity.h"
using namespace std;

Entity::Entity(vector<Component*> cps,vector<TYPE_NAME> attributes,map<TYPE_NAME,string> attributes_default_value)
{
    components = cps;
    add_optimal_attribute(attributes, attributes_default_value);
}

void Entity::add_optimal_attribute(vector<TYPE_NAME> attributes,map<TYPE_NAME,string> attributes_default_value)
{
  for(auto& at:attributes)
  {
    if(get_component22(at) == NULL)
    {
      string value = attributes_default_value[at];
      if(value == "")
        throw Error("Bad Request");
      components.push_back(build_component(at,value));
    }
  }
}

Component* Entity::get_component22(TYPE_NAME tn)
{
  for(auto& cp:components)
    if(cp->get_type() == tn)
      return cp;
  return NULL;
}
