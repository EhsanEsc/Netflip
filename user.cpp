
#include "user.h"
#include "film.h"
using namespace std;

std::vector<TYPE_NAME> USER_PRIMARY_LIST = {TYPE_NAME::USER_NAME,TYPE_NAME::AGE} ;
std::vector<TYPE_NAME> USER_OPTIMAL_LIST;

User::User(vector<Component*> comps)
: Entity(comps,USER_PRIMARY_LIST,USER_OPTIMAL_LIST)
{
  id = get_new_id();
  for(auto& tn: USER_OPTIMAL_LIST)
  {
    if(get_component22(tn) == NULL)
    {
      // if(tn == )
    }
  }
}

int User::get_new_id()
{
  static int id = 0;
  id++;
  cout << "ID " << id << " Is Created! " << endl;
  return id;
}

void User::show()
{
  cout << "User id: " << id << " # ";
  cout << "User Name: " << get_component<Name>(TYPE_NAME::USER_NAME)->get_value() << endl;
}

bool User::is_pubisher() { return ispub; }
