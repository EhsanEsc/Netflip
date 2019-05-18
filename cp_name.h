
#ifndef CP_NAME_H
#define CP_NAME_H

#include "component.h"

class Name : public Component
{
public:
  Name(std::string ct,TYPE_NAME tp);
  bool validation() const;
  std::string get_value() const;
  void edit_name(std::string new_content);
  void edit(std::string ct);
  void set(std::string ct);
private:
  std::string content;
};

#endif
