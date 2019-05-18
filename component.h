
#ifndef COMPONENT_H
#define COMPONENT_H

#include "sources.h"
#include<string>

class Component
{
public:
  Component(TYPE_NAME tp);
  virtual bool validation() const = 0;
  virtual std::string get_value() const = 0;
  virtual void edit(std::string ct) = 0;

  bool operator<(const Component& cp) const ;
  bool operator==(const Component& cp) const ;

  TYPE_NAME get_type();
  void set_filter_type(FILTER_TYPE ft);
  FILTER_TYPE get_filter_type();
private:
  TYPE_NAME type = TYPE_NAME::UNDEFINED;
  FILTER_TYPE ftype = FILTER_TYPE::EXACT;
};

#endif
