
#include "cp_bool.h"
using namespace std;

Bool::Bool(string ct,TYPE_NAME tp)
: Component(ct,tp)
{
  if(validation() == false)
    return;
  set(ct);
}

bool Bool::validation() const
{
  if(raw_content=="true" || raw_content=="false")
    return true;
  return false;
}

string Bool::get_value() const
{
  if(content)
    return "true";
  else
    return "false";
}

bool Bool::get() { return content; }
void Bool::edit(std::string ct) { set(ct); }
void Bool::set(std::string ct)
{
  if(ct == "true")
    content = true;
  else if(ct == "false")
    content = false;
}
