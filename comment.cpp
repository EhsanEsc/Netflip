
#include "comment.h"
using namespace std;

std::vector<TYPE_NAME> COMMENT_ATTRIBUTE = {TYPE_NAME::ID,TYPE_NAME::SUMMARY} ;
map<TYPE_NAME,string> attributes_default_value = {
  {TYPE_NAME::ID, ""},
  {TYPE_NAME::SUMMARY, ""}
};

Comment::Comment(std::vector<Component*> comps, bool rep)
: Entity(comps, COMMENT_ATTRIBUTE, attributes_default_value)
{
  be_reply = rep;
}
Comment::Comment(int id,std::string content, bool rep)
: Entity(vector<Component*>{new Number(to_string(id),TYPE_NAME::ID),new Name(content,TYPE_NAME::SUMMARY)}, COMMENT_ATTRIBUTE, attributes_default_value)
{
  be_reply = rep;
}

bool Comment::is_reply(){ return be_reply; }

void Comment::add_reply(Comment* cm)
{
  if(is_reply() == true)
    throw Error("Bad Request");
  replys.push_back(cm);
}

void Comment::print()
{
  int id = get_component<Number>(TYPE_NAME::ID)->get();
  string content = get_component<Name>(TYPE_NAME::SUMMARY)->get_value();
  cout << id << ". " << content << endl;
  for(int i=0 ; i<replys.size() ; i++)
  {
    Comment* cm = replys[i];
    cout << cm->get_component<Number>(TYPE_NAME::ID)->get() << "." << i+1 << ".";
    cout << cm->get_component<Name>(TYPE_NAME::SUMMARY)->get_value() << endl;
  }
}
