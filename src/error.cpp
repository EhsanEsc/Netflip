
#include "error.h"
using namespace std;

Error::Error(string str) { msg = str; }
string Error::what() { return msg; }
