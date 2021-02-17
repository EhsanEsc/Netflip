#ifndef PASSWORD_H
#define PASSWORD_H

#include "component.h"

class Password : public Component
{
public:
  Password(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
  void set(std::string ct);
  void edit(std::string ct);

private:
  std::string content;
  std::string hash_password(std::string pass);
};

#endif
