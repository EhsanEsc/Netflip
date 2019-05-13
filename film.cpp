
#include "film.h"
#include "user.h"
using namespace std;

std::vector<TYPE_NAME> FILM_ATTRIBUTE = {TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
  TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR} ;
map<TYPE_NAME,string> attributes_default_value = {
};

Film::Film(vector<Component*> comps)
: Entity(comps,FILM_ATTRIBUTE,attributes_default_value)
{
  id = get_new_id();
  cout << "FILM with id: " << id << " Created! " << endl;
}

int Film::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}
