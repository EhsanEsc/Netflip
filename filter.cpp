
#include "filter.h"
using namespace std;

Component* Filter_interface::search(vector<Component*> vc, TYPE_NAME tn)
{
  for(auto&u: vc)
    if(u->get_type() == tn)
      return u;
  return NULL;
}
