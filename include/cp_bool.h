
#ifndef BOOL_H
#define BOOL_H

#include "component.h"

class Bool : public Component
{
public:
  Bool(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
  bool get();

  void edit(std::string ct);
  void set(std::string ct);
private:
  bool content;
};

#endif
