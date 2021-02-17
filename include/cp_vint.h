
#ifndef CP_VINT_H
#define CP_VINT_H

#include "component.h"
#include <vector>
#include <string>

class Vint : public Component
{
public:
  Vint(std::string ct,TYPE_NAME tp);
  bool validation() const ;
  void edit(std::string ct){}
  std::string get_value() const ;

  void push(int x);
  void pop(int x);
  double get_average() const ;
  int get_sum() const ;
private:
  std::vector<int> numbers;
};

#endif
