
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
      if(*(u->get_component22(cp->get_type())) == *cp)
        return u;
    return NULL;
  }
  template<typename T> vector<T*> filter_min(vector<T*> vt, Component* cp)
  {
    vector<T*>res;
    for(auto& u:vt)
      if(*cp < *(u->get_component22(cp->get_type())))
        res.push_back(u);
    return res;
  }
  template<typename T> vector<T*> sort(vector<T*> vt, TYPE_NAME tn)
  {
    // bubble sort
    for(int i=0;i<int(vt.size())-1;i++)
    {
      for(int j=0;j<int(vt.size())-i-1;j++)
      {
        cout << i << " " << j << endl;
        if(*(vt[j+1]->get_component22(tn))<*(vt[j]->get_component22(tn)))
          swap(vt[j],vt[j+1]);
      }
    }
    return vt;
  }
  // template User* find_exact<User>(vector<User*> vt, Component* cp);
}

#endif
