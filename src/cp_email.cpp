
#include "cp_email.h"
#include <regex>
using namespace std;

Email::Email(string ct,TYPE_NAME tp)
: Component(ct,tp)
{
  if(validation() == false)
    return;
  set(ct);
}

bool Email::validation() const
{
  const regex pattern
     ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  return regex_match(raw_content, pattern);
}

string Email::get_value() const { return content; }
void Email::edit(std::string ct) { set(ct); }
void Email::set(std::string ct) { content = ct; }
