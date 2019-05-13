
#include "cp_number.h"
using namespace std;

Number::Number(string ct,TYPE_NAME tp)
: Component(tp)
{
  for(auto u:ct)
    if(u<'0' || u>'9')
      throw Error("Bad Request");

  int num = stoi(ct);
  number = num;
  min_value = -INF;
  max_value = INF;
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

void Number::set(int x)
{
  number = x;
}
