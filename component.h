
#ifndef COMPONENT_H
#define COMPONENT_H

#include "sources.h"

class Component
{
public:
  Component(TYPE_NAME tp);
  TYPE_NAME get_type();
  virtual bool validation() const = 0;
  // virtual bool operator<(const Component& cp) const ;
  // virtual bool operator==(const Component& cp) const ;
private:
  TYPE_NAME type;
};

#endif
