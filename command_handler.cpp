
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
      if(line=="") continue;
      vector<string> command = split_line(line);
      vector<Component*> input = get_parametrs(command);
      COMMAND_TYPE ctype = get_command_type(command,input);
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
        server->get_profit(input);
      } else if(ctype == COMMAND_TYPE::FOLLOW) {
        server->follow_user(input);
      } else if(ctype == COMMAND_TYPE::SEARCHPOSTED) {
        server->show_posted_films(input);
      } else if(ctype == COMMAND_TYPE::SEARCHFILMS) {
        server->show_all_films(input);
      } else if(ctype == COMMAND_TYPE::SEARCHPURCHASED) {
        server->show_purchased_films(input);
      } else if(ctype == COMMAND_TYPE::GETFILM) {
        server->show_film_detail(input);
      } else if(ctype == COMMAND_TYPE::ADDMONEY) {
        server->add_money(input);
      } else if(ctype == COMMAND_TYPE::BUYFILM) {
        server->buy_film(input);
      } else if(ctype == COMMAND_TYPE::RATEFILM) {
        server->rate_film(input);
      } else if(ctype == COMMAND_TYPE::ADDCOMMENT) {
        server->add_comment(input);
      } else if(ctype == COMMAND_TYPE::REPLYCOMMENT) {
        server->reply_comment(input);
      } else if(ctype == COMMAND_TYPE::DELETECOMMENT) {
        server->delete_comment(input);
      } else if(ctype == COMMAND_TYPE::SHOWNOTI) {
        server->show_notis(input);
      } else if(ctype == COMMAND_TYPE::SHOWSEENNOTI) {
        server->show_seen_notis(input);
      }

      if(ctype != COMMAND_TYPE::SEARCHPOSTED && ctype != COMMAND_TYPE::SHOWFOLOWERS && ctype != COMMAND_TYPE::SEARCHFILMS
        && ctype != COMMAND_TYPE::GETFILM && ctype != COMMAND_TYPE::SEARCHPURCHASED && ctype != COMMAND_TYPE::SHOWNOTI
        && ctype != COMMAND_TYPE::SHOWSEENNOTI )
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

map<COMMAND_TYPE,pair<string,string>> command_method_cache = {
  {COMMAND_TYPE::SIGNUP, {"POST","signup"}},
  {COMMAND_TYPE::LOGIN, {"POST","login"}},
  {COMMAND_TYPE::POSTFILM, {"POST","films"}},
  {COMMAND_TYPE::EDITFILM, {"PUT","films"}},
  {COMMAND_TYPE::DELETEFILM, {"DELETE","films"}},
  {COMMAND_TYPE::SHOWFOLOWERS, {"GET","followers"}},
  {COMMAND_TYPE::GETPROFIT, {"POST","money"}},
  {COMMAND_TYPE::FOLLOW, {"POST","followers"}},
  {COMMAND_TYPE::SEARCHPOSTED, {"GET","published"}},
  {COMMAND_TYPE::SEARCHFILMS, {"GET","films"}},
  {COMMAND_TYPE::SEARCHPURCHASED, {"GET","purchased"}},
  {COMMAND_TYPE::GETFILM, {"GET","films"}},
  {COMMAND_TYPE::ADDMONEY, {"POST","money"}},
  {COMMAND_TYPE::BUYFILM, {"POST","buy"}},
  {COMMAND_TYPE::RATEFILM, {"POST","rate"}},
  {COMMAND_TYPE::ADDCOMMENT, {"POST","comments"}},
  {COMMAND_TYPE::REPLYCOMMENT, {"POST","replies"}},
  {COMMAND_TYPE::DELETECOMMENT, {"DELETE","comments"}},
  {COMMAND_TYPE::SHOWNOTI, {"GET","notifications"}},
  {COMMAND_TYPE::SHOWSEENNOTI, {"GET","notifications"}}
};

map<COMMAND_TYPE, vector<TYPE_NAME>> command_primary_list = {
  {COMMAND_TYPE::SIGNUP , vector<TYPE_NAME>{TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,TYPE_NAME::AGE}},
  {COMMAND_TYPE::LOGIN , vector<TYPE_NAME>{TYPE_NAME::USER_NAME,TYPE_NAME::PASSWORD}},
  {COMMAND_TYPE::POSTFILM , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
    TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR}},
  {COMMAND_TYPE::EDITFILM , vector<TYPE_NAME>{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::DELETEFILM , vector<TYPE_NAME>{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::SHOWFOLOWERS , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::GETPROFIT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::FOLLOW , vector<TYPE_NAME>{TYPE_NAME::USERID}},
  {COMMAND_TYPE::SEARCHPOSTED , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SEARCHFILMS , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SEARCHPURCHASED , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::GETFILM , vector<TYPE_NAME>{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::ADDMONEY , vector<TYPE_NAME>{TYPE_NAME::MONEY}},
  {COMMAND_TYPE::BUYFILM , vector<TYPE_NAME>{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::RATEFILM , vector<TYPE_NAME>{TYPE_NAME::FILMID, TYPE_NAME::RATE}},
  {COMMAND_TYPE::ADDCOMMENT , vector<TYPE_NAME>{TYPE_NAME::FILMID, TYPE_NAME::CONTENT}},
  {COMMAND_TYPE::REPLYCOMMENT , vector<TYPE_NAME>{TYPE_NAME::FILMID, TYPE_NAME::COMMENTID, TYPE_NAME::CONTENT}},
  {COMMAND_TYPE::DELETECOMMENT , vector<TYPE_NAME>{TYPE_NAME::FILMID, TYPE_NAME::COMMENTID}},
  {COMMAND_TYPE::SHOWNOTI , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SHOWSEENNOTI , vector<TYPE_NAME>{TYPE_NAME::LIMIT}}
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
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::SEARCHFILMS , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::SEARCHPURCHASED , vector<TYPE_NAME>{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::GETFILM , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::ADDMONEY , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::BUYFILM , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::RATEFILM , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::ADDCOMMENT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::REPLYCOMMENT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::DELETECOMMENT , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SHOWNOTI , vector<TYPE_NAME>{}},
  {COMMAND_TYPE::SHOWSEENNOTI , vector<TYPE_NAME>{}}
  // {COMMAND_TYPE:: , vector<TYPE_NAME>{}}
};

COMMAND_TYPE CommandHandler::get_command_type(vector<string> command, vector<Component*> input)
{
  if(command.size() < 2)
    throw Error("Bad Request");
  vector<COMMAND_TYPE> ct, res;
  pair<string,string> method = {command[0],command[1]};
  for(auto u:command_method_cache)
    if(u.second == method)
      ct.push_back(u.first);
  if(ct.size() == 0)
    throw Error("Not Found");
  for(auto u:ct)
    if(check_validate(u, input))
      res.push_back(u);
  if(res.size() != 1)
    throw Error("Bad Request");
  return res[0];
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
