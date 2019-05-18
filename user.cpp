
#include "user.h"
#include "film.h"
#include "notification.h"

using namespace std;

std::vector<TYPE_NAME> USER_ATTRIBUTE = {TYPE_NAME::USERID,TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,
  TYPE_NAME::AGE,TYPE_NAME::ISPUB,TYPE_NAME::MONEY} ;
map<TYPE_NAME,string> attribute_default_value = {
  {TYPE_NAME::USERID, "0"},
  {TYPE_NAME::ISPUB, "false"},
  {TYPE_NAME::MONEY, "0"}
};

User::User(vector<Component*> comps)
: Entity(comps,USER_ATTRIBUTE,attribute_default_value)
{
  get_component<Number>(TYPE_NAME::USERID)->set(get_new_id());
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

void User::buy_film(Film* fl)
{
  int money = stoi(get_component<Number>(TYPE_NAME::MONEY)->get_value());
  int price = stoi(fl->get_component<Number>(TYPE_NAME::PRICE)->get_value());
  if(price > money)
    throw Error("Permision Denied");
  get_component<Number>(TYPE_NAME::MONEY)->add(-price);
  purchased_films.push_back(fl);
}

std::vector<Film*> User::get_posted_films() { return posted_films; }
std::vector<Film*> User::get_purchased_films() { return purchased_films; }

std::vector<User*> User::get_followers() { return followers; }
bool User::is_publisher() { return get_component<Bool>(TYPE_NAME::ISPUB)->get_value() == "true"; }
bool User::is_purchased(Film* fl)
{
  for(auto& u:purchased_films)
    if(u == fl)
      return true;
  return false;
}

void User::add_noti(Noti* nt)
{
  unread_notis.push_back(nt);
}

void User::show_notis()
{
  cout << "#. Notification Message" << endl;
  for(int i=unread_notis.size()-1,j=0;i>=0;i--,j++)
  {
    cout << j+1 << ". ";
    unread_notis[i]->print();
  }
  for(int i=0;i<unread_notis.size();i++)
    seen_notis.push_back(unread_notis[i]);
  unread_notis.clear();
}

void User::show_seen_notis(int limit)
{
  cout << "#. Notification Message" << endl;
  for(int i=seen_notis.size()-1,j=0 ; i>=0 && j<limit ; i--,j++)
  {
    cout << j+1 << ". ";
    seen_notis[i]->print();
  }
}

int User::get_rate(Film* fl)
{
  if(rate_film_cache.find(fl) == rate_film_cache.end())
    return -1;
  return rate_film_cache[fl];
}
void User::add_rate(Film* fl,int score)
{
  rate_film_cache[fl] = score;
}
