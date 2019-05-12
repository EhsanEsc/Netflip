
#include "sources.h"
using namespace std;

int INF = 1e7+22;
int MAX_CNT_COMPONENT = 22;

std::map<std::string,TYPE_NAME> type_name_cache = {
  {"user_name",TYPE_NAME::USER_NAME},
  {"age",TYPE_NAME::AGE}
};
TYPE_NAME get_type_name(string key)
{
  if(type_name_cache.find(key) == type_name_cache.end())
    return TYPE_NAME::UNDEFINED;
  return type_name_cache[key];
}

Error::Error(string str) { msg = str; }
string Error::what() { return msg; }
