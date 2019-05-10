
#include "sources.h"
using namespace std;

int INF = 1e7+22;
int MAX_CNT_COMPONENT = 22;

std::map<std::string,TYPE_NAME> type_name_cache = {
  {"user_name",TYPE_NAME::USER_NAME},
  {"age",TYPE_NAME::AGE}
};

Error::Error(string str) { msg = str; }
string Error::what() { return msg; }
