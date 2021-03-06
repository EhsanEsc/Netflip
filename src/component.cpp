
#include "cp_headers.h"
#include<map>
using namespace std;

Component::Component(string rtc, TYPE_NAME tp){ type = tp,raw_content=rtc; }
TYPE_NAME Component::get_type() { return type; }

void Component::set_filter_type(FILTER_TYPE ft) { ftype = ft; }
FILTER_TYPE Component::get_filter_type() { return ftype; }

bool Component::operator<(const Component& cp) const
{
  if(get_value()[0]>='0' && get_value()[0]<='9') // has minor bug...
    return stoi(get_value()) < stoi(cp.get_value());
  return get_value() < cp.get_value();
}

bool Component::operator==(const Component& cp) const
{
  return get_value() == cp.get_value();
}

Component* build_component(string key, string value)
{
  string bkey = key;
  if(key.substr(0,4) == "min_" || key.substr(0,4) == "max_")
    key = key.substr(4);
  Component* cp = build_component(get_type_name(key),value);
  if(bkey.substr(0,4) == "min_")
    cp->set_filter_type(FILTER_TYPE::MIN);
  if(bkey.substr(0,4) == "max_")
    cp->set_filter_type(FILTER_TYPE::MAX);
  return cp;
}

Component* build_component(TYPE_NAME tn,string value)
{
  if(tn == TYPE_NAME::USER_NAME || tn == TYPE_NAME::NAME || tn == TYPE_NAME::SUMMARY || tn == TYPE_NAME::DIRECTOR
      || tn == TYPE_NAME::CONTENT) {
    return (new Name(value, tn));
  } else if(tn == TYPE_NAME::EMAIL){
    return (new Email(value, tn));
  } else if(tn == TYPE_NAME::PASSWORD){
    return (new Password(value, tn));
  } else if(tn == TYPE_NAME::AGE || tn == TYPE_NAME::YEAR || tn == TYPE_NAME::LENGTH || tn == TYPE_NAME::USERID
     || tn == TYPE_NAME::PRICE  || tn == TYPE_NAME::MONEY || tn == TYPE_NAME::FILMID || tn == TYPE_NAME::RATE
     || tn == TYPE_NAME::COMMENTID || tn == TYPE_NAME::NOTIID || tn == TYPE_NAME::LIMIT) {
    return (new Number(value,tn));
  } else if(tn == TYPE_NAME::ISPUB) {
    return (new Bool(value, tn));
  } else if(tn == TYPE_NAME::FILMRATE) {
    return (new Vint(value,tn));
  } else if(tn == TYPE_NAME::UNDEFINED) {
    return NULL;
  }
  return NULL;
}

// has minor bug
std::map<std::string,TYPE_NAME> type_name_cache = {
  {"user_name",TYPE_NAME::USER_NAME},
  {"username",TYPE_NAME::USER_NAME},
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
  {"film_id", TYPE_NAME::FILMID},
  {"user_id", TYPE_NAME::USERID},
  {"comment_id" , TYPE_NAME::COMMENTID},
  {"amount", TYPE_NAME::MONEY},
  {"rate" , TYPE_NAME::RATE},
  {"score", TYPE_NAME::RATE},
  {"content", TYPE_NAME::CONTENT},
  {"limit", TYPE_NAME::LIMIT}
};

TYPE_NAME get_type_name(string key)
{
  if(type_name_cache.find(key) == type_name_cache.end())
    return TYPE_NAME::UNDEFINED;
  return type_name_cache[key];
}
