
#ifndef CP_NAME_H
#define CP_NAME_H

#include "component.h"

class Name : public Component
{
public:
  Name(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
private:
  std::string content;
};

#endif
