
#ifndef FILTER_H
#define FILTER_H

#include "error.h"
#include "cp_headers.h"
#include "entity_headers.h"
using namespace std;

class Filter
{
public:
  static Filter* get_instance();

  // FOR Entity
  template<typename T> T* find_exact(vector<T*> vt, Component* cp)
  {
    for(auto& u:vt)
      if(*(u->get_component_bytype(cp->get_type())) == *cp)
        return u;
    return NULL;
  }
  template<typename T> vector<T*> filter_min(vector<T*> vt, Component* cp)
  {
    vector<T*>res;
    for(auto& u:vt)
      if(*cp < *(u->get_component_bytype(cp->get_type())))
        res.push_back(u);
    return res;
  }
  template<typename T> vector<T*> filter_max(vector<T*> vt, Component* cp)
  {
    vector<T*>res;
    for(auto& u:vt)
      if(*(u->get_component_bytype(cp->get_type())) < *cp)
        res.push_back(u);
    return res;
  }
  template<typename T> vector<T*> filter_exact(vector<T*> vt, Component* cp)
  {
    vector<T*>res;
    for(auto& u:vt)
      if(*cp == *(u->get_component_bytype(cp->get_type())))
        res.push_back(u);
    return res;
  }
  template<typename T> vector<T*> sort(vector<T*> vt, TYPE_NAME tn)
  {
    // bubble sort
    for(int i=0;i<int(vt.size())-1;i++)
      for(int j=0;j<int(vt.size())-i-1;j++)
        if(*(vt[j+1]->get_component_bytype(tn))<*(vt[j]->get_component_bytype(tn)))
          swap(vt[j],vt[j+1]);
    return vt;
  }
  template<typename T> vector<T*> filter(vector<T*> vt, Component* cp)
  {
    vector<T*> res;
    if(cp->get_filter_type() == FILTER_TYPE::MIN)
      res = filter_min(vt,cp);
    else if(cp->get_filter_type() == FILTER_TYPE::MAX)
      res = filter_max(vt,cp);
    else if(cp->get_filter_type() == FILTER_TYPE::EXACT)
      res = filter_exact(vt,cp);
    return res;
  }

  // For Components
  Component* search(vector<Component*> vc, TYPE_NAME tn);

  template<typename T> T* search_exact(vector<Component*> vt, TYPE_NAME tn)
  {
    return dynamic_cast<T*>(search(vt,tn));
  }

private:
  static Filter* instance;
};

#endif
