
#ifndef SORCES_H
#define SORCES_H

#include<bits/stdc++.h>

extern int INF;
extern int MAX_CNT_COMPONENT;

enum class TYPE_NAME
{
  USER_NAME,
  AGE,
  UNDEFINED
};
extern std::map<std::string,TYPE_NAME> type_name_cache;
TYPE_NAME get_type_name(std::string key);

class Error
{
public:
  Error(std::string str);
  std::string what();
private:
  std::string msg;
};

#endif
