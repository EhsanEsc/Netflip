
#ifndef CP_NUMBER_H
#define CP_NUMBER_H

#include "component.h"

class Number : public Component
{
public:
  Number(int num,TYPE_NAME tp,int mn,int mx);
  bool validation() const ;
private:
  int number;
  int min_value;
  int max_value;
};

#endif
