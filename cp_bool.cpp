
#include "cp_bool.h"
using namespace std;

Bool::Bool(string ct,TYPE_NAME tp)
: Component(tp)
{
  set(ct);
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

void Bool::edit(std::string ct)
{
  set(ct);
}

void Bool::set(std::string ct)
{
  if(ct == "true")
    content = true;
  else if(ct == "false")
    content = false;
  else
    throw Error("Bad Request");
}
