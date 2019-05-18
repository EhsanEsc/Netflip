
#include "film.h"
#include "user.h"
#include "comment.h"
#include "filter.h"
#include <iostream>
using namespace std;

std::vector<TYPE_NAME> FILM_ATTRIBUTE = {TYPE_NAME::FILMID,TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
  TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR,TYPE_NAME::MONEY,TYPE_NAME::FILMRATE} ;
map<TYPE_NAME,string> attributes_default_value2 = {
  {TYPE_NAME::FILMID , "0"},
  {TYPE_NAME::MONEY, "0"},
  {TYPE_NAME::FILMRATE, "0"}
};

Film::Film(vector<Component*> comps, User* _publisher)
: Entity(comps,FILM_ATTRIBUTE,attributes_default_value2)
{
  get_component<Number>(TYPE_NAME::FILMID)->set(get_new_id());
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
  publisher->add_money(calc_paid_money(cp->get()));
  cp->set(0);
}

int Film::calc_paid_money(int profit)
{
  double rate = get_component<Vint>(TYPE_NAME::FILMRATE)->get_average();
  if(rate < 5)
    return profit*8/10;
  else if(rate < 8)
    return profit*9/10;
  else
    return profit*95/100;
}

void Film::print_details()
{
  cout << "Id = " << get_component<Number>(TYPE_NAME::FILMID)->get_value() << endl;
  cout << "Director = " << get_component<Name>(TYPE_NAME::DIRECTOR)->get_value() << endl;
  cout << "Length = " << get_component<Number>(TYPE_NAME::LENGTH)->get_value() << endl;
  cout << "Year = " << get_component<Number>(TYPE_NAME::YEAR)->get_value() << endl;
  cout << "Summary = " << get_component<Name>(TYPE_NAME::SUMMARY)->get_value() << endl;
  cout << "Rate = " << get_component<Vint>(TYPE_NAME::FILMRATE)->get_average() << endl;
  cout << "Price = " << get_component<Number>(TYPE_NAME::PRICE)->get_value() << endl;
}

void Film::print_comments()
{
  for(auto& u:comments)
    u->print();
}

void Film::add_comment(std::string content, User* writer)
{
  int new_id = get_new_comment_id();
  comments.push_back(new Comment(new_id, content, false, writer));
}

void Film::reply_comment(Component* cmid, std::string content)
{
  Comment* cm = Filter::get_instance()->find_exact(comments, cmid);
  if(cm->is_reply())
    throw Error("Permision Denied");
  cm->add_reply(new Comment(cm->get_new_reply_comment_id(), content, true, publisher));
}

void Film::delete_comment(Component* cmid)
{
  for(int i=0;i<comments.size();i++)
  {
    Component* comment_id = comments[i]->get_component22(TYPE_NAME::COMMENTID);
    if(*comment_id == *cmid)
    {
      comments.erase(comments.begin()+i);
      return;
    }
  }
}

User* Film::get_comment_writer(Component* cmid)
{

  Comment* cm = Filter::get_instance()->find_exact(comments, cmid);
  return cm->get_writer();
}

int Film::get_new_comment_id()
{
  last_comment_id++;
  return last_comment_id;
}
