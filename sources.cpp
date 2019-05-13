
#include "sources.h"
#include "cp_headers.h"
using namespace std;

int INF = 1e7+22;
int MAX_CNT_COMPONENT = 22;

std::map<std::string,TYPE_NAME> type_name_cache = {
  {"user_name",TYPE_NAME::USER_NAME},
  {"email", TYPE_NAME::EMAIL},
  {"password", TYPE_NAME::PASSWORD},
  {"age",TYPE_NAME::AGE},
  {"publisher",TYPE_NAME::ISPUB},
  {"name", TYPE_NAME::NAME},
  {"year", TYPE_NAME::YEAR},
  {"length", TYPE_NAME::LENGTH},
  {"price", TYPE_NAME::PRICE},
  {"summary", TYPE_NAME::SUMMARY},
  {"director", TYPE_NAME::DIRECTOR},
  {"money", TYPE_NAME::MONEY},
};

TYPE_NAME get_type_name(string key)
{
  if(type_name_cache.find(key) == type_name_cache.end())
    return TYPE_NAME::UNDEFINED;
  return type_name_cache[key];
}

Error::Error(string str) { msg = str; }
string Error::what() { return msg; }

Component* build_component(string key, string value)
{
  return build_component(get_type_name(key),value);
}

Component* build_component(TYPE_NAME tn,string value)
{
  if(tn == TYPE_NAME::USER_NAME || tn == TYPE_NAME::NAME || tn == TYPE_NAME::SUMMARY || tn == TYPE_NAME::DIRECTOR) {
    return (new Name(value, tn));
  } else if(tn == TYPE_NAME::EMAIL){
    return (new Email(value, tn));
  } else if(tn == TYPE_NAME::PASSWORD){
    return (new Password(value, tn));
  } else if(tn == TYPE_NAME::AGE || tn == TYPE_NAME::YEAR || tn == TYPE_NAME::LENGTH || tn == TYPE_NAME::PRICE  || tn == TYPE_NAME::MONEY) {
    return (new Number(value,tn));
  } else if(tn == TYPE_NAME::ISPUB) {
    return (new Bool(value, tn));
  } else if(tn == TYPE_NAME::UNDEFINED) {
    throw Error("Bad Request");
  }
}

std::ostream& operator << (std::ostream& os, const TYPE_NAME& obj)
{
   os << static_cast<std::underlying_type<TYPE_NAME>::type>(obj);
   return os;
}
