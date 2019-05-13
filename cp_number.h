
#ifndef CP_NUMBER_H
#define CP_NUMBER_H

#include "component.h"

class Number : public Component
{
public:
  Number(std::string ct,TYPE_NAME tp);
  bool validation() const ;
  void set(int x);
  std::string get_value() const ;
private:
  int number;
  int min_value;
  int max_value;
};

#endif
