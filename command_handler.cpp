
#include "command_handler.h"
using namespace std;

CommandHandler* CommandHandler::instance = NULL;
CommandHandler* CommandHandler::get_instance()
{
  if(instance == NULL)
    instance = new CommandHandler();
  return instance;
}

void CommandHandler::run()
{
  Server* server = Server::get_instance();

  string line ;
  while(getline(cin, line))
  {
    try{
      vector<string> command = split_line(line);
      COMMAND_TYPE ctype = get_command_type(command);
      vector<Component*> input = get_parametrs(command);
      if(check_validate(ctype, input) == false)
        throw Error("Bad Request");

      if(ctype == COMMAND_TYPE::ADD) {
        server->add_user(input);
      } else if(ctype == COMMAND_TYPE::SHOW) {
        server->show(input);
      } else if(ctype == COMMAND_TYPE::SHOWMIN) {
        server->showmin(input);
      } else if(ctype == COMMAND_TYPE::EDITNAME) {
        server->editname(input);
      }
      if(ctype != COMMAND_TYPE::ADD) {
        remove_input(input);
      }
    } catch(Error& err) {
      cerr << err.what() << endl;
    }
  }
}

vector<string> CommandHandler::split_line(string line)
{
  vector<string> res;
  int en=0;
  for(int st=0;st<line.size();st++)
  {
    if(line[st] == ' ') continue;
    en = st;
    while(en<line.size() && line[en] != ' ')
    { en++; }
    res.push_back(line.substr(st,en-st));
    st=en;
  }
  return res;
}

map<pair<string,string>,COMMAND_TYPE> command_type_cache = {
  {{"add","user"} , COMMAND_TYPE::ADD},
  {{"show","user"} , COMMAND_TYPE::SHOW},
  {{"show","more_age"} , COMMAND_TYPE::SHOWMIN},
  {{"edit","user_name"}, COMMAND_TYPE::EDITNAME}
};

COMMAND_TYPE CommandHandler::get_command_type(vector<string> command)
{
  if(command.size()<3 || command[2] != "?")
    throw Error("Bad Request");
  if(command_type_cache.find({command[0],command[1]}) == command_type_cache.end())
    throw Error("Bad Request");
  return command_type_cache[{command[0], command[1]}];
}

vector<Component*> CommandHandler::get_parametrs(vector<string> command)
{
  if(command.size()<3 || command.size()%2 == 0)
    throw Error("Bad Request");
  vector<Component*> res;
  for(int i=3;i<command.size();i+=2)
    res.push_back(build_component(command[i],command[i+1]));
  return res;
}

bool CommandHandler::check_validate(COMMAND_TYPE ctype, vector<Component*> params)
{
  return true;
}

Component* CommandHandler::build_component(string key,string value)
{
  TYPE_NAME tn = get_type_name(key);
  if(tn == TYPE_NAME::USER_NAME)
  {
    Name* cp = new Name(value, tn);
    return cp;
  } else if(tn == TYPE_NAME::AGE) {
    Number* cp = new Number(stoi(value),tn,1,99);
    return cp;
  } else if(tn == TYPE_NAME::UNDEFINED) {
    throw Error("Bad Request");
  }
}

void CommandHandler::remove_input(vector<Component*> input)
{
  for(auto& u:input)
    delete u;
}
