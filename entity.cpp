
#include "entity.h"
using namespace std;

Entity::Entity(vector<Component*> cps, vector<TYPE_NAME> pr, vector<TYPE_NAME> opt, vector<TYPE_NAME> be)
{
    components = cps;
    primary_list = pr;
    optimal_list = opt;
    be_list = be;
    if(validation() == false)
      throw "Bad Request";
}

Component* Entity::get_component(TYPE_NAME tp)
{
  for(auto& u:components)
    if(u->get_type() == tp)
      return u;
  return NULL;
}

bool Entity::validation()
{
  bool is_exist[MAX_CNT_COMPONENT];
  bool is_exist_optimal[MAX_CNT_COMPONENT];
  for(int i=0;i<MAX_CNT_COMPONENT;i++)
    is_exist[i] = is_exist_optimal[i] = false;
  for(auto& cp:components)
  {
    bool is_valid = false;
    for(int i=0;i<primary_list.size();i++)
    {
      if(cp->get_type() == primary_list[i])
      {
        if(is_exist[i])
          return false;
        is_exist[i] = true;
        is_valid = true;
        break;
      }
    }
    for(int i=0;i<optimal_list.size();i++)
    {
      if(cp->get_type() == optimal_list[i])
      {
        if(is_exist_optimal[i])
          return false;
        is_exist_optimal[i] = true;
        is_valid = true;
        break;
      }
    }
    if(!is_valid)
      return false;
  }
  for(int i=0;i<primary_list.size();i++)
  {
    if(!is_exist[i])
      return false;
  }
  return true;
}

int Entity::get_id()
{
  return id;
}
