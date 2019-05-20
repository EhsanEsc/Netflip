
#ifndef COMPONENT_H
#define COMPONENT_H

#include "error.h"
#include<string>
#include<vector>

enum class TYPE_NAME
{
  FILMID,
  USERID,
  COMMENTID,
  NOTIID,
  USER_NAME,
  EMAIL,
  PASSWORD,
  AGE,
  ISPUB,
  NAME,
  YEAR,
  LENGTH,
  PRICE,
  SUMMARY,
  DIRECTOR,
  FILMRATE,
  MONEY,
  RATE,
  CONTENT,
  LIMIT,
  UNDEFINED
};
TYPE_NAME get_type_name(std::string key);

enum class FILTER_TYPE
{
  EXACT,
  MIN,
  MAX,
  UNDEFINED
};

class Component
{
public:
  Component(std::string rct, TYPE_NAME tp);
  virtual bool validation() const = 0;
  virtual std::string get_value() const = 0;
  virtual void edit(std::string ct) = 0;

  bool operator<(const Component& cp) const ;
  bool operator==(const Component& cp) const ;

  TYPE_NAME get_type();
  void set_filter_type(FILTER_TYPE ft);
  FILTER_TYPE get_filter_type();
protected:
  TYPE_NAME type = TYPE_NAME::UNDEFINED;
  FILTER_TYPE ftype = FILTER_TYPE::EXACT;
  std::string raw_content;
};
Component* build_component(std::string key,std::string value);
Component* build_component(TYPE_NAME tn, std::string value);

typedef std::vector<Component*> Parametrs;
typedef std::vector<TYPE_NAME> Typelist; 
#endif
