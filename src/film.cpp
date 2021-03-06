
#include "film.h"
#include "user.h"
#include "comment.h"
#include "filter.h"
#include <iostream>
#include <sstream>
using namespace std;

Typelist FILM_ATTRIBUTE = {TYPE_NAME::FILMID,TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
  TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR,TYPE_NAME::MONEY,TYPE_NAME::FILMRATE} ;
map<TYPE_NAME,string> attributes_default_value2 = {
  {TYPE_NAME::FILMID , "0"},
  {TYPE_NAME::MONEY, "0"},
  {TYPE_NAME::FILMRATE, "0"}
};

Film::Film(Parametrs comps, User* _publisher)
: Entity(comps,FILM_ATTRIBUTE,attributes_default_value2)
{
  get_component<Number>(TYPE_NAME::FILMID)->set(get_new_id());
  publisher = _publisher;
}

int Film::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}

int Film::get_id()
{
  return get_component<Number>(TYPE_NAME::FILMID)->get();
}

User* Film::get_publisher()
{
  return publisher;
}

void Film::pay_publisher(User* admin)
{
  int profit = get_component<Number>(TYPE_NAME::MONEY)->get();
  publisher->add_money(profit);
  admin->spend_money(profit);
  get_component<Number>(TYPE_NAME::MONEY)->set(0);
}

void Film::sold_out()
{
  int price = get_component<Number>(TYPE_NAME::PRICE)->get();
  get_component<Number>(TYPE_NAME::MONEY)->add(calc_paid_money(price));
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

std::vector<std::string> Film::print_details()
{
  vector<string> res;
  stringstream ss;
  ss << "Id = " << get_component<Number>(TYPE_NAME::FILMID)->get_value();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Director = " << get_component<Name>(TYPE_NAME::DIRECTOR)->get_value();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Length = " << get_component<Number>(TYPE_NAME::LENGTH)->get_value();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Year = " << get_component<Number>(TYPE_NAME::YEAR)->get_value();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Summary = " << get_component<Name>(TYPE_NAME::SUMMARY)->get_value();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Rate = " << get_component<Vint>(TYPE_NAME::FILMRATE)->get_average();
  res.push_back(ss.str()) , ss.str(" ");
  ss << "Price = " << get_component<Number>(TYPE_NAME::PRICE)->get_value();
  res.push_back(ss.str()) , ss.str(" ");

  return res;
}

std::vector<std::string> Film::print_comments()
{
  vector<string> res;
  for(auto& u:comments)
    res.push_back(u->print());
  return res;
}

void Film::add_comment(std::string content, User* writer)
{
  int new_id = get_new_comment_id();
  comments.push_back(new Comment(new_id, content, false, writer));
}

void Film::reply_comment(Component* cmid, std::string content)
{
  Comment* cm = Filter::get_instance()->find_exact(comments, cmid);
  if(cm == NULL)
    throw Error(NOT_FOUND_MSG);
  cm->add_reply(new Comment(cm->get_new_reply_comment_id(), content, true, publisher));
}

void Film::delete_comment(Component* cmid)
{
  for(int i=0;i<int(comments.size());i++)
  {
    Component* comment_id = comments[i]->get_component_bytype(TYPE_NAME::COMMENTID);
    if(*comment_id == *cmid)
    {
      comments.erase(comments.begin()+i);
      return;
    }
  }
  throw Error(NOT_FOUND_MSG);
}

User* Film::get_comment_writer(Component* cmid)
{
  Comment* cm = Filter::get_instance()->find_exact(comments, cmid);
  if(cm == NULL)
    return NULL;
  return cm->get_writer();
}

int Film::get_new_comment_id()
{
  last_comment_id++;
  return last_comment_id;
}
