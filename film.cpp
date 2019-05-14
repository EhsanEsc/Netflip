
#include "film.h"
#include "user.h"
#include "comment.h"
using namespace std;

std::vector<TYPE_NAME> FILM_ATTRIBUTE = {TYPE_NAME::ID,TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
  TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR,TYPE_NAME::MONEY,TYPE_NAME::RATE} ;
map<TYPE_NAME,string> attributes_default_value2 = {
  {TYPE_NAME::ID , "0"},
  {TYPE_NAME::MONEY, "0"},
  {TYPE_NAME::RATE, "0"}
};

Film::Film(vector<Component*> comps, User* _publisher)
: Entity(comps,FILM_ATTRIBUTE,attributes_default_value2)
{
  get_component<Number>(TYPE_NAME::ID)->set(get_new_id());
  publisher = _publisher;

  // cout << "FILM with id: " << get_component<Number>(TYPE_NAME::ID)->get_value() << " Created! " << endl;
}

int Film::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}

User* Film::get_publisher()
{
  return publisher;
}

void Film::pay_publisher()
{
  Number* cp = get_component<Number>(TYPE_NAME::MONEY);
  publisher->add_money(cp->get());
  cp->set(0);
}

void Film::print_details()
{
  cout << "Details of Film " << get_component<Name>(TYPE_NAME::NAME)->get_value() << endl;
  cout << "Id = " << get_component<Number>(TYPE_NAME::ID)->get_value() << endl;
  cout << "Director = " << get_component<Name>(TYPE_NAME::DIRECTOR)->get_value() << endl;
  cout << "Length = " << get_component<Number>(TYPE_NAME::LENGTH)->get_value() << endl;
  cout << "Year = " << get_component<Number>(TYPE_NAME::YEAR)->get_value() << endl;
  cout << "Summary = " << get_component<Name>(TYPE_NAME::SUMMARY)->get_value() << endl;
  cout << "Rate = " << get_component<Number>(TYPE_NAME::RATE)->get_average() << endl;
  cout << "Price = " << get_component<Number>(TYPE_NAME::PRICE)->get_value() << endl;
}

void Film::print_comments()
{
  for(auto& u:comments)
    u->print();
}

void Film::add_comment(std::string content)
{
  int new_id = get_new_comment_id();
  comments.push_back(new Comment(new_id, content, false));
}

void Film::reply_comment(int id, std::string content)
{
  cout << "WRITE REPLY COMMENT IN FILM.CPP" << endl;
}

int Film::get_new_comment_id()
{
  last_comment_id++;
  return last_comment_id;
}
