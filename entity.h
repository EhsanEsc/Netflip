
#ifndef ENTITY_H
#define ENTITY_H

#include "cp_headers.h"

class Entity
{
public:
  Entity(std::vector<Component*> cps, std::vector<TYPE_NAME> primary_list, std::vector<TYPE_NAME> optimal_list);
  Component* get_component22(TYPE_NAME tp);
  template<typename T> T* get_component(TYPE_NAME tp) const
  {
    for(auto& u:components)
      if(u->get_type() == tp)
        return dynamic_cast<T*>(u);
    return NULL;
  }
  int get_id();
protected:
  int id;
  std::vector<Component*> components;

  bool validation(std::vector<TYPE_NAME> primary_list, std::vector<TYPE_NAME> optimal_list);
};

#endif
