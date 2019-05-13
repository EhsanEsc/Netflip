
#include "film.h"
#include "user.h"
using namespace std;

std::vector<TYPE_NAME> FILM_PRIMARY_LIST = {TYPE_NAME::NAME,TYPE_NAME::AGE} ;
std::vector<TYPE_NAME> FILM_OPTIMAL_LIST;

Film::Film(vector<Component*> comps)
: Entity(comps,FILM_PRIMARY_LIST,FILM_OPTIMAL_LIST)
{
  id = get_new_id();
  for(auto& tn: FILM_OPTIMAL_LIST)
  {
    if(get_component22(tn) == NULL)
    {
      // if(tn == )
    }
  }
}

int Film::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}
