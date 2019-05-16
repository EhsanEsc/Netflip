
#ifndef SORCES_H
#define SORCES_H

#include<bits/stdc++.h>

extern int INF;
extern int MAX_CNT_COMPONENT;

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
  MONEY,
  RATE,
  CONTENT,
  UNDEFINED
};
extern std::map<std::string,TYPE_NAME> type_name_cache;
TYPE_NAME get_type_name(std::string key);
std::ostream& operator << (std::ostream& os, const TYPE_NAME& obj);

class Error
{
public:
  Error(std::string str);
  std::string what();
private:
  std::string msg;
};

class Component;
Component* build_component(std::string key,std::string value);
Component* build_component(TYPE_NAME tn, std::string value);

enum class FILTER_TYPE
{
  EXACT,
  MIN,
  MAX,
  UNDEFINED
};

#endif
