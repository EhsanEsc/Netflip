
#include "user.h"
using namespace std;

std::vector<TYPE_NAME> USER_PRIMARY_LIST = {TYPE_NAME::USER_NAME,TYPE_NAME::AGE} ;
std::vector<TYPE_NAME> USER_OPTIMAL_LIST;
std::vector<TYPE_NAME> USER_BE_LIST;

User::User(vector<Component*> comps)
: Entity(comps,USER_PRIMARY_LIST,USER_OPTIMAL_LIST,USER_BE_LIST)
{
  id = get_new_id();
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
