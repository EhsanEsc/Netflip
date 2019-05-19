
#ifndef ENTITY_H
#define ENTITY_H

#include "cp_headers.h"
#include<map>

class Entity
{
public:
  Entity(std::vector<Component*> cps,std::vector<TYPE_NAME> attributes,std::map<TYPE_NAME,std::string> attributes_default_value);
  Component* get_component22(TYPE_NAME tp);
  template<typename T> T* get_component(TYPE_NAME tp)
  {
    return dynamic_cast<T*>(get_component22(tp));
  }
protected:
  std::vector<Component*> components;

  void add_optimal_attribute(std::vector<TYPE_NAME> attributes,std::map<TYPE_NAME,std::string> attributes_default_value);
};

#endif