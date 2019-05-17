
#include "cp_password.h"
using namespace std;

Password::Password(string ct,TYPE_NAME tp)
: Component(tp)
{
  content = hash_password(ct);
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

std::string Password::hash_password(std::string pass)
{
  long long hash = 0;
  for (auto& c:pass)
  {
      srand(pass.size()*c);
      hash += 33 + rand()%92;
  }
  return to_string(hash);
}
