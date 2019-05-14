
#ifndef CP_NUMBER_H
#define CP_NUMBER_H

#include "component.h"

class Number : public Component
{
public:
  Number(std::string ct,TYPE_NAME tp);
  bool validation() const ;
  void set(int x);
  int get();
  void add(int x);
  std::string get_value() const ;

  void push(int x);
  double get_average() ;
private:
  int number;
  int min_value;
  int max_value;

  int sum = 0;
  int ted = 0;
};

#endif
