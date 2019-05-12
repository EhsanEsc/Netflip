
#include "cp_bool.h"
using namespace std;

Bool::Bool(string ct,TYPE_NAME tp)
: Component(tp)
{
  if(ct == "true")
    content = true;
  else if(ct == "false")
    content = false;
  else
    throw Error("Bad Request");
}

bool Bool::validation() const
{
  return true;
}

string Bool::get_value() const
{
  if(content)
    return "true";
  else
    return "false";
}
