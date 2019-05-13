
#include "film.h"
#include "user.h"
using namespace std;

std::vector<TYPE_NAME> FILM_ATTRIBUTE = {TYPE_NAME::ID,TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
  TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR} ;
map<TYPE_NAME,string> attributes_default_value = {
  {TYPE_NAME::ID , "0"}
};

Film::Film(vector<Component*> comps, User* _publisher)
: Entity(comps,FILM_ATTRIBUTE,attributes_default_value)
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
