
#include "cp_number.h"
using namespace std;

Number::Number(int num,TYPE_NAME tp,int mn=-INF,int mx=INF)
: Component(tp)
{
  number = num;
  min_value = mn;
  max_value = mx;
  if(validation() == false)
    throw Error("Bad Request");
}
bool Number::validation() const
{
  if(number < min_value || number > max_value)
    return false;
  return true;
}

string Number::get_value() const
{
  return to_string(number);
}
