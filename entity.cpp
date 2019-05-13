
#include "entity.h"
using namespace std;

Entity::Entity(vector<Component*> cps, vector<TYPE_NAME> primary_list, vector<TYPE_NAME> optimal_list)
{
    components = cps;
    if(validation(primary_list, optimal_list) == false)
      throw "Bad Request";
}

Component* Entity::get_component22(TYPE_NAME tn)
{
  for(auto& cp:components)
    if(cp->get_type() == tn)
      return cp;
  return NULL;
}

bool Entity::validation(vector<TYPE_NAME> primary_list, vector<TYPE_NAME> optimal_list)
{
  for(int i=0;i<components.size();i++)
    for(int j=i+1;j<components.size();j++)
      if(components[i]->get_type() == components[j]->get_type())
        return false;

  for(auto& u:primary_list)
  {
    bool exist = false;
    for(auto& cp:components)
      exist |= cp->get_type()==u;
    if(exist == false)
      return false;
  }

  for(auto& cp:components)
  {
    bool valid = false;
    for(auto& u:primary_list)
      valid |= u==cp->get_type();
    for(auto& u:optimal_list)
      valid |= u==cp->get_type();
    if(valid == false)
      return false;
  }

  return true;
}

int Entity::get_id()
{
  return id;
}
