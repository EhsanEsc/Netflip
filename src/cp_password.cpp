
#include "cp_password.h"
#include "md5.h"

using namespace std;

Password::Password(string ct,TYPE_NAME tp)
: Component(ct,tp)
{
  if(validation() == false)
    return;
  set(ct);
  raw_content = ct;
}

bool Password::validation() const { return true; }
string Password::get_value() const { return content; }
std::string Password::hash_password(std::string pass) { return md5(pass); }
void Password::edit(std::string ct) { content = ct; }
void Password::set(std::string ct) { content = hash_password(ct); }
