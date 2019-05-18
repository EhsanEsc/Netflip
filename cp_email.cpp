
#include "cp_email.h"
using namespace std;

Email::Email(string ct,TYPE_NAME tp)
: Component(tp)
{
  set(ct);
  if(validation() == false)
    throw Error("Bad Request");
}

bool Email::validation() const
{
  // check if is valid email
  return true;
}

string Email::get_value() const
{
  return content;
}

void Email::edit(std::string ct)
{
  set(ct);
}
void Email::set(std::string ct)
{
  content = ct;
}
