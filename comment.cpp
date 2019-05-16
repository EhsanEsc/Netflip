
#include "comment.h"
using namespace std;

std::vector<TYPE_NAME> COMMENT_ATTRIBUTE = {TYPE_NAME::COMMENTID,TYPE_NAME::CONTENT} ;
map<TYPE_NAME,string> attributes_default_value = {
  {TYPE_NAME::COMMENTID, ""},
  {TYPE_NAME::CONTENT, ""}
};

Comment::Comment(std::vector<Component*> comps, bool rep)
: Entity(comps, COMMENT_ATTRIBUTE, attributes_default_value)
{
  be_reply = rep;
}
Comment::Comment(int id,std::string content, bool rep)
: Entity(vector<Component*>{new Number(to_string(id),TYPE_NAME::COMMENTID),new Name(content,TYPE_NAME::CONTENT)}, COMMENT_ATTRIBUTE, attributes_default_value)
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
  int id = get_component<Number>(TYPE_NAME::COMMENTID)->get();
  string content = get_component<Name>(TYPE_NAME::CONTENT)->get_value();
  cout << id << ". " << content << endl;
  for(int i=0 ; i<replys.size() ; i++)
  {
    Comment* cm = replys[i];
    cout << id << ".";
    cout << cm->get_component<Number>(TYPE_NAME::COMMENTID)->get() << ". ";
    cout << cm->get_component<Name>(TYPE_NAME::CONTENT)->get_value() << endl;
  }
}

int Comment::get_new_reply_comment_id()
{
  last_reply_comment_id++;
  return last_reply_comment_id;
}
