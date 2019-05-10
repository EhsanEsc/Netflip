
#include "cp_name.h"
using namespace std;

Name::Name(string ct,TYPE_NAME tp)
: Component(tp)
{
  content = ct;
  if(validation() == false)
    throw Error("Bad Request");
}

bool Name::validation() const
{
  if(content.size()==0)
    return false;
  if(content[0]<'a' || content[0]>'z')
    return false;
  return true;
}
