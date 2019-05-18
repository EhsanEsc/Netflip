
#include "cp_name.h"
using namespace std;

Name::Name(string ct,TYPE_NAME tp)
: Component(tp)
{
  set(ct);
  if(validation() == false)
    throw Error("Bad Request");
}

bool Name::validation() const
{
  if(content.size()==0)
    return false;
  if(content[0]>='0' && content[0]<='9')
    return false;
  return true;
}

string Name::get_value() const
{
  return content;
}

// delete this
void Name::edit_name(string new_content)
{
  content = new_content;
}

void Name::edit(std::string ct)
{
  set(ct);
}

void Name::set(std::string ct)
{
  content = ct;
}
