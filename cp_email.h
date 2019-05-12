
#ifndef EMAIL_H
#define EMAIL_H

#include "component.h"

class Email : public Component
{
public:
  Email(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
private:
  std::string content;
};

#endif
