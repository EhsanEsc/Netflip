
#include "cp_vint.h"
using namespace std;

Vint::Vint(string ct,TYPE_NAME tp)
: Component(tp)
{}
bool Vint::validation() const
{
  return true;
}

string Vint::get_value() const
{
  return to_string(get_average());
}

void Vint::push(int x)
{
  numbers.push_back(x);
  sum += x;
}

double Vint::get_average() const
{
  if(numbers.size()==0) return 0;
  return 1.0*sum/numbers.size();
}
