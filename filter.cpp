
#include "filter.h"
using namespace std;

int Filter::find_exact(vector<Entity*> container, Component* cp)
{
  for(auto& u: container)
  {
    Component* c = u->get_component(cp->get_type());
    if(*c == *cp)
      return u->get_id();
  }
  return NULL;
}

vector<int> Filter::filter_min(vector<Entity*> container, Component* cp)
{
  vector<int> res;
  for(auto& u: container)
  {
    Component* c = u->get_component(cp->get_type());
    if(*cp < *c)
      res.push_back(u->get_id());
  }
  return res;
}
