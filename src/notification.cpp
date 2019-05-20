
#include "notification.h"
#include <iostream>
using namespace std;

Typelist NOTI_ATTRIBUTE = { TYPE_NAME::CONTENT } ;
map<TYPE_NAME,string> attribute_default_value3 = {
};

Noti::Noti(Parametrs params)
: Entity(params,NOTI_ATTRIBUTE,attribute_default_value3)
{}
void Noti::print()
{
  cout << get_component_bytype(TYPE_NAME::CONTENT)->get_value() << endl;
}
