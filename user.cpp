
#include "user.h"
#include "film.h"
using namespace std;

std::vector<TYPE_NAME> USER_ATTRIBUTE = {TYPE_NAME::ID,TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,
  TYPE_NAME::AGE,TYPE_NAME::ISPUB,TYPE_NAME::MONEY} ;
map<TYPE_NAME,string> attribute_default_value = {
  {TYPE_NAME::ID, "0"},
  {TYPE_NAME::ISPUB, "false"},
  {TYPE_NAME::MONEY, "0"}
};

User::User(vector<Component*> comps)
: Entity(comps,USER_ATTRIBUTE,attribute_default_value)
{
  get_component<Number>(TYPE_NAME::ID)->set(get_new_id());
  // show();
}


int User::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}

void User::show()
{
  cout << "User --> ";
  for(auto& u:components)
    cout << u->get_value() << " ";
  cout << endl;
}

void User::add_posted_film(Film* fl)
{
  posted_films.push_back(fl);
}

void User::add_money(int gold)
{
  Number* nu = get_component<Number>(TYPE_NAME::MONEY);
  nu->set(nu->get()+gold);
}

void User::follow(User* us)
{
  following.push_back(us);
}

void User::add_follower(User* us)
{
  followers.push_back(us);
}

std::vector<Film*> User::get_posted_films() { return posted_films; }

std::vector<User*> User::get_followers() { return followers; }
bool User::is_publisher() { return get_component<Bool>(TYPE_NAME::ISPUB)->get_value() == "true"; }
