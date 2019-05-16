
#include "notification.h"
using namespace std;

std::vector<TYPE_NAME> NOTI_ATTRIBUTE = { TYPE_NAME::CONTENT } ;
map<TYPE_NAME,string> attribute_default_value3 = {
};

Noti::Noti(std::vector<Component*> params)
: Entity(params,NOTI_ATTRIBUTE,attribute_default_value3)
{}
void Noti::print()
{
  cout << get_component22(TYPE_NAME::CONTENT)->get_value() << endl;
}
