
#ifndef EMAIL_H
#define EMAIL_H

#include "component.h"

class Email : public Component
{
public:
  Email(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
  void edit(std::string ct);
  void set(std::string ct);
private:
  std::string content;
};

#endif
