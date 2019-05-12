
#ifndef FILTER_H
#define FILTER_H

#include "sources.h"
#include "cp_headers.h"
#include "entity_headers.h"
using namespace std;

namespace Filter_interface
{
  template<typename T> T* find_exact(vector<T*> vt, Component* cp)
  {
    for(auto& u:vt)
      if(*(u->get_component(cp->get_type())) == *cp)
        return u;
    return NULL;
  }
  template<typename T> vector<T*> filter_min(vector<T*> vt, Component* cp)
  {
    vector<T*>res;
    for(auto& u:vt)
      if(*cp < *(u->get_component(cp->get_type())))
        res.push_back(u);
    return res;
  }
  // template User* find_exact<User>(vector<User*> vt, Component* cp);
}

#endif
