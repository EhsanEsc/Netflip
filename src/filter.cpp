
#include "filter.h"
using namespace std;

Component* Filter::search(vector<Component*> vc, TYPE_NAME tn)
{
  for(auto&u: vc)
    if(u->get_type() == tn)
      return u;
  return NULL;
}

Filter* Filter::instance = NULL;
Filter* Filter::get_instance()
{
  if(instance == NULL)
    instance = new Filter();
  return instance;
}
