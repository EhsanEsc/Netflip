
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
      vector<Component*> input = get_parametrs(command);
      COMMAND_TYPE ctype = get_command_type(command);
      if(check_validate(ctype, input) == false)
        throw Error("Bad Request");

      if(ctype == COMMAND_TYPE::SIGNUP) {
        server->add_user(input);
      } else if(ctype == COMMAND_TYPE::LOGIN) {
        server->login(input);
      } else if(ctype == COMMAND_TYPE::POSTFILM) {
        server->add_film(input);
      } else if(ctype == COMMAND_TYPE::EDITFILM) {
        server->edit_film(input);
      } else if(ctype == COMMAND_TYPE::DELETEFILM) {
        server->delete_film(input);
      } else if(ctype == COMMAND_TYPE::SHOWFOLOWERS) {
        server->show_followers(input);
      } else if(ctype == COMMAND_TYPE::GETPROFIT) {
        server->get_money(input);
      } else if(ctype == COMMAND_TYPE::FOLLOW) {
        server->follow_user(input);
      } else if(ctype == COMMAND_TYPE::SEARCHPOSTED) {
        server->show_posted_films(input);
      }
      if(ctype != COMMAND_TYPE::SEARCHPOSTED && ctype != COMMAND_TYPE::SHOWFOLOWERS)
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
  {{"POST","signup"}, COMMAND_TYPE::SIGNUP},
  {{"POST","login"}, COMMAND_TYPE::LOGIN},
  {{"POST","films"}, COMMAND_TYPE::POSTFILM},
  {{"PUT","films"}, COMMAND_TYPE::EDITFILM},
  {{"DELETE","films"}, COMMAND_TYPE::DELETEFILM},
  {{"POST","followers"}, COMMAND_TYPE::FOLLOW},
  {{"GET","films"}, COMMAND_TYPE::SEARCHPOSTED}
};

map<pair<string,string>,COMMAND_TYPE> alone_command_cache = {
  {{"GET","followers"}, COMMAND_TYPE::SHOWFOLOWERS},
  {{"POST","money"}, COMMAND_TYPE::GETPROFIT}
};

map<COMMAND_TYPE, vector<TYPE_NAME>> command_primary_list = {
  {COMMAND_TYPE::SIGNUP , vector<TYPE_NAME>{TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,TYPE_NAME::AGE}},
  {COMMAND_TYPE::LOGIN , vector<TYPE_NAME>{TYPE_NAME::USER_NAME,TYPE_NAME::PASSWORD}},
  {COMMAND_TYPE::POSTFILM , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
    TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR}},
  {COMMAND_TYPE::EDITFILM , vector<TYPE_NAME>{TYPE_NAME::ID}},
  {COMMAND_TYPE::DELETEFILM , vector<TYPE_NAME>{TYPE_NAME::ID}},
  {COMMAND_TYPE::SHOWFOLOWERS , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::GETPROFIT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::FOLLOW , vector<TYPE_NAME>{TYPE_NAME::ID}},
  {COMMAND_TYPE::SEARCHPOSTED , vector<TYPE_NAME>{}}
  // {COMMAND_TYPE:: , vector<TYPE_NAME>{}}
};

map<COMMAND_TYPE, vector<TYPE_NAME>> command_optimal_list = {
  {COMMAND_TYPE::SIGNUP , vector<TYPE_NAME>{TYPE_NAME::ISPUB}},
  {COMMAND_TYPE::LOGIN , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::POSTFILM , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::EDITFILM , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
    TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR}},
  {COMMAND_TYPE::DELETEFILM , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SHOWFOLOWERS , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::GETPROFIT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::FOLLOW , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SEARCHPOSTED , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}}
  // {COMMAND_TYPE:: , vector<TYPE_NAME>{}}
};

COMMAND_TYPE CommandHandler::get_command_type(vector<string> command)
{
  if(command.size()<2)
    throw Error("Bad Request");
  if(command.size()==2)
  {
    if(alone_command_cache.find({command[0],command[1]}) == alone_command_cache.end())
      throw Error("Bad Request");
    return alone_command_cache[{command[0],command[1]}];
  }
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
      if(params[i]->get_type() == params[j]->get_type() && params[i]->get_filter_type() == params[j]->get_filter_type())
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
