
#include "cp_password.h"
using namespace std;

Password::Password(string ct,TYPE_NAME tp)
: Component(tp)
{
  // do something magic stuff with ct
  content = ct;
  if(validation() == false)
    throw Error("Bad Request");
}

bool Password::validation() const
{
  return true;
}

string Password::get_value() const
{
  return content;
}
