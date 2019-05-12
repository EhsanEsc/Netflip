
#include "film.h"
using namespace std;

std::vector<TYPE_NAME> USER_PRIMARY_LIST = {TYPE_NAME::USER_NAME,TYPE_NAME::AGE} ;
std::vector<TYPE_NAME> USER_OPTIMAL_LIST;
std::vector<TYPE_NAME> USER_BE_LIST;

User::User(vector<Component*> comps)
: Entity(comps,USER_PRIMARY_LIST,USER_OPTIMAL_LIST,USER_BE_LIST)
{
  id = get_new_id();
}

int Film::get_new_id()
{
  static int id = 0;
  id++;
  return id;
}
