
#include "cp_number.h"
using namespace std;

Number::Number(string ct,TYPE_NAME tp)
: Component(ct,tp)
{
  if(validation() == false)
    return;
  set(ct);
}
bool Number::validation() const
{
  for(auto u:raw_content)
    if(u<'0' || u>'9')
      return false;
  if(raw_content[0] == '0' && raw_content.size()!=1 )
    return false;
  return true;
}

string Number::get_value() const { return to_string(number); }
void Number::set(int x) { number = x; }
void Number::add(int x) { number += x; }
int Number::get() { return number; }
void Number::edit(std::string ct){ set(ct); }
void Number::set(std::string ct) { number = stoi(ct); }
