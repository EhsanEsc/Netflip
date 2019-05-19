
#include "cp_number.h"
using namespace std;

Number::Number(string ct,TYPE_NAME tp)
: Component(tp)
{
  set(ct);
  if(validation() == false)
    throw Error("Bad Request");
}
bool Number::validation() const
{
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

void Number::add(int x)
{
  number += x;
}

int Number::get() { return number; }

void Number::edit(std::string ct)
{
  set(ct);
}
void Number::set(std::string ct)
{
  for(auto u:ct)
    if(u<'0' || u>'9')
      throw Error("Bad Request");
  if(ct[0] == '0' && ct.size()!=1 )
    throw Error("Bad Request");
  int num = stoi(ct);
  number = num;
  min_value = -INF;
  max_value = INF;
}
