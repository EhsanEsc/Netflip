
#include "user.h"
#include "film.h"
using namespace std;

std::vector<TYPE_NAME> USER_ATTRIBUTE = {TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,TYPE_NAME::AGE,TYPE_NAME::ISPUB} ;
map<TYPE_NAME,string> attribute_default_value = {
  {TYPE_NAME::USER_NAME, ""},
  {TYPE_NAME::EMAIL, ""},
  {TYPE_NAME::PASSWORD, ""},
  {TYPE_NAME::AGE, ""},
  {TYPE_NAME::ISPUB, "false"}
};

User::User(vector<Component*> comps)
: Entity(comps,USER_ATTRIBUTE,attribute_default_value)
{
  id = get_new_id();
  show();
}


int User::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}

void User::show()
{
  cout << "User id: " << id << " -> ";
  for(auto& u:components)
    cout << u->get_value() << " ";
  cout << endl;
}

bool User::is_publisher() { return get_component<Bool>(TYPE_NAME::ISPUB)->get_value() == "true"; }
