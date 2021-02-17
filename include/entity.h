
#ifndef ENTITY_H
#define ENTITY_H

#include "cp_headers.h"
#include<map>

class Entity
{
public:
  Entity(Parametrs cps,Typelist attributes,std::map<TYPE_NAME,std::string> attributes_default_value);
  Component* get_component_bytype(TYPE_NAME tp);
  template<typename T> T* get_component(TYPE_NAME tp) { return dynamic_cast<T*>(get_component_bytype(tp)); }
  bool is_ok();
protected:
  Parametrs components;

  void add_optimal_attribute(Typelist attributes,std::map<TYPE_NAME,std::string> attributes_default_value);
  bool valid;
};

#endif
