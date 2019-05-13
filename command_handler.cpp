
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

      if(ctype == COMMAND_TYPE::SIGNUP) {
        server->add_user(input);
      }

      cout << "OK" << endl;
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
  {{"POST","signup"}, COMMAND_TYPE::SIGNUP}
};

map<COMMAND_TYPE, vector<TYPE_NAME>> command_primary_list = {
  {COMMAND_TYPE::SIGNUP , vector<TYPE_NAME>{TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,TYPE_NAME::AGE}}
  // {COMMAND_TYPE:: , vector<TYPE_NAME>{}}
};

map<COMMAND_TYPE, vector<TYPE_NAME>> command_optimal_list = {
  {COMMAND_TYPE::SIGNUP , vector<TYPE_NAME>{TYPE_NAME::ISPUB}}
  // {COMMAND_TYPE:: , vector<TYPE_NAME>{}}
};

COMMAND_TYPE CommandHandler::get_command_type(vector<string> command)
{
  if(command.size()<2)
    throw Error("Bad Request");
  if(command_type_cache.find({command[0],command[1]}) == command_type_cache.end())
    throw Error("Bad Request");
  return command_type_cache[{command[0], command[1]}];
}

vector<Component*> CommandHandler::get_parametrs(vector<string> command)
{
  if(command.size()<3)
    return vector<Component*>();
  if(command[2] != "?" || command.size()%2 == 0)
    throw Error("Bad Request");
  vector<Component*> res;
  for(int i=3;i<command.size();i+=2)
    res.push_back(build_component(command[i],command[i+1]));
  return res;
}

bool CommandHandler::check_validate(COMMAND_TYPE ctype, vector<Component*> params)
{
  vector<TYPE_NAME> primary_list = command_primary_list[ctype];
  vector<TYPE_NAME> optimal_list = command_optimal_list[ctype];

  for(int i=0;i<params.size();i++)
    for(int j=i+1;j<params.size();j++)
      if(params[i]->get_type() == params[j]->get_type())
        return false;

  for(auto& u:primary_list)
  {
    bool exist = false;
    for(auto& cp:params)
      exist |= (cp->get_type()==u);
    if(exist == false)
      return false;
  }

  for(auto& cp:params)
  {
    bool valid = false;
    for(auto& u:primary_list)
      valid |= u==cp->get_type();
    for(auto& u:optimal_list)
      valid |= u==cp->get_type();
    if(valid == false)
      return false;
  }
  
  return true;
}

void CommandHandler::remove_input(vector<Component*> input)
{
  for(auto& u:input)
    delete u;
}
