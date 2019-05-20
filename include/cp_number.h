
#ifndef CP_NUMBER_H
#define CP_NUMBER_H

#include "component.h"

class Number : public Component
{
public:
  Number(std::string ct,TYPE_NAME tp);
  bool validation() const ;
  std::string get_value() const ;
  int get();
  void edit(std::string ct);

  void set(std::string ct);
  void set(int x);
  void add(int x);
private:
  int number;
};

#endif
