
#include "cp_name.h"
using namespace std;

Name::Name(string ct,TYPE_NAME tp)
: Component(ct,tp)
{
  if(validation() == false)
    return;
  set(ct);
}

bool Name::validation() const { return true; }
string Name::get_value() const { return content; }
void Name::edit(std::string ct) { set(ct); }
void Name::set(std::string ct) { content = ct; }
