
#ifndef COMPONENT_H
#define COMPONENT_H

#include "sources.h"

class Component
{
public:
  Component(TYPE_NAME tp);
  TYPE_NAME get_type();
  virtual bool validation() const = 0;
  bool operator<(const Component& cp) const ;
  bool operator==(const Component& cp) const ;
  virtual std::string get_value() const = 0;
private:
  TYPE_NAME type;
};

#endif
