
#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"

class Entity
{
public:
  Entity(std::vector<Component*> cps, std::vector<TYPE_NAME> pr, std::vector<TYPE_NAME> opt, std::vector<TYPE_NAME> be);
  // template<typename T> T* get_component(TYPE_NAME tp);
  Component* get_component(TYPE_NAME tp);
  int get_id();
protected:
  int id;
  std::vector<Component*> components;
  std::vector<TYPE_NAME> primary_list;
  std::vector<TYPE_NAME> optimal_list;
  std::vector<TYPE_NAME> be_list;

  bool validation();
};

#endif
