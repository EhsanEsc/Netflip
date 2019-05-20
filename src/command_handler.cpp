
#include "command_handler.h"
#include "component.h"
#include<map>
#include<iostream>
using namespace std;

const string SPLITER = "?";

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
      Parametrs input = get_parametrs(command);
      COMMAND_TYPE ctype = get_command_type(command,input);

      server->check_validate(ctype, input);
      switch(ctype)
      {
        case COMMAND_TYPE::SIGNUP:
          server->add_user(input);
          break;
        case COMMAND_TYPE::LOGIN:
          server->login(input);
          break;
        case COMMAND_TYPE::LOGOUT:
          server->logout(input);
          break;
        case COMMAND_TYPE::POSTFILM:
          server->add_film(input);
          break;
        case COMMAND_TYPE::EDITFILM:
          server->edit_film(input);
          break;
        case COMMAND_TYPE::DELETEFILM:
          server->delete_film(input);
          break;
        case COMMAND_TYPE::SHOWFOLOWERS:
          server->show_followers(input);
          break;
        case COMMAND_TYPE::GETPROFIT:
          server->get_profit(input);
          break;
        case COMMAND_TYPE::FOLLOW:
          server->follow_user(input);
          break;
        case COMMAND_TYPE::SEARCHPOSTED:
          server->show_posted_films(input);
          break;
        case COMMAND_TYPE::SEARCHFILMS:
          server->show_all_films(input);
          break;
        case COMMAND_TYPE::SEARCHPURCHASED:
          server->show_purchased_films(input);
          break;
        case COMMAND_TYPE::GETFILM:
          server->show_film_detail(input);
          break;
        case COMMAND_TYPE::ADDMONEY:
          server->add_money(input);
          break;
        case COMMAND_TYPE::BUYFILM:
          server->buy_film(input);
          break;
        case COMMAND_TYPE::RATEFILM:
          server->rate_film(input);
          break;
        case COMMAND_TYPE::ADDCOMMENT:
          server->add_comment(input);
          break;
        case COMMAND_TYPE::REPLYCOMMENT:
          server->reply_comment(input);
          break;
        case COMMAND_TYPE::DELETECOMMENT:
          server->delete_comment(input);
          break;
        case COMMAND_TYPE::SHOWNOTI:
          server->show_notis(input);
          break;
        case COMMAND_TYPE::SHOWSEENNOTI:
          server->show_seen_notis(input);
          break;
        case COMMAND_TYPE::SHOWMONEY:
          server->show_money(input);
          break;
        case COMMAND_TYPE::UNDEFINED:
          throw Error(BAD_REQUEST_MSG);
          break;
      }

      if(ctype != COMMAND_TYPE::SEARCHPOSTED && ctype != COMMAND_TYPE::SHOWFOLOWERS && ctype != COMMAND_TYPE::SEARCHFILMS
        && ctype != COMMAND_TYPE::GETFILM && ctype != COMMAND_TYPE::SEARCHPURCHASED && ctype != COMMAND_TYPE::SHOWNOTI
        && ctype != COMMAND_TYPE::SHOWSEENNOTI && ctype != COMMAND_TYPE::SHOWMONEY)
        cout << SUCCESS_COMMAND_MSG << endl;

    } catch(Error& err) {
      cout << err.what() << endl;
    }
  }
}

vector<string> CommandHandler::split_line(string line)
{
  vector<string> res;
  int en=0;
  for(int st=0;st<int(line.size());st++)
  {
    if(line[st] == ' ') continue;
    en = st;
    while(en<int(line.size()) && line[en] != ' ')
    { en++; }
    res.push_back(line.substr(st,en-st));
    st=en;
  }
  return res;
}

map<COMMAND_TYPE,pair<string,string>> command_method_cache = {
  {COMMAND_TYPE::SIGNUP, {"POST","signup"}},
  {COMMAND_TYPE::LOGIN, {"POST","login"}},
  {COMMAND_TYPE::LOGOUT, {"POST","logout"}},
  {COMMAND_TYPE::POSTFILM, {"POST","films"}},
  {COMMAND_TYPE::EDITFILM, {"POST","put_films"}},
  {COMMAND_TYPE::DELETEFILM, {"POST","delete_films"}},
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
  {COMMAND_TYPE::DELETECOMMENT, {"POST","delete_comments"}},
  {COMMAND_TYPE::SHOWNOTI, {"GET","notifications"}},
  {COMMAND_TYPE::SHOWSEENNOTI, {"GET","notifications read"}},
  {COMMAND_TYPE::SHOWMONEY, {"GET","money"}}
};

map<COMMAND_TYPE, Typelist> command_primary_list = {
  {COMMAND_TYPE::SIGNUP , Typelist{TYPE_NAME::USER_NAME,TYPE_NAME::EMAIL,TYPE_NAME::PASSWORD,TYPE_NAME::AGE}},
  {COMMAND_TYPE::LOGIN , Typelist{TYPE_NAME::USER_NAME,TYPE_NAME::PASSWORD}},
  {COMMAND_TYPE::LOGOUT , Typelist{}},
  {COMMAND_TYPE::POSTFILM , Typelist{TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
    TYPE_NAME::PRICE,TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR}},
  {COMMAND_TYPE::EDITFILM , Typelist{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::DELETEFILM , Typelist{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::SHOWFOLOWERS , Typelist{}},
  {COMMAND_TYPE::GETPROFIT , Typelist{}},
  {COMMAND_TYPE::FOLLOW , Typelist{TYPE_NAME::USERID}},
  {COMMAND_TYPE::SEARCHPOSTED , Typelist{}},
  {COMMAND_TYPE::SEARCHFILMS , Typelist{}},
  {COMMAND_TYPE::SEARCHPURCHASED , Typelist{}},
  {COMMAND_TYPE::GETFILM , Typelist{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::ADDMONEY , Typelist{TYPE_NAME::MONEY}},
  {COMMAND_TYPE::BUYFILM , Typelist{TYPE_NAME::FILMID}},
  {COMMAND_TYPE::RATEFILM , Typelist{TYPE_NAME::FILMID, TYPE_NAME::RATE}},
  {COMMAND_TYPE::ADDCOMMENT , Typelist{TYPE_NAME::FILMID, TYPE_NAME::CONTENT}},
  {COMMAND_TYPE::REPLYCOMMENT , Typelist{TYPE_NAME::FILMID, TYPE_NAME::COMMENTID, TYPE_NAME::CONTENT}},
  {COMMAND_TYPE::DELETECOMMENT , Typelist{TYPE_NAME::FILMID, TYPE_NAME::COMMENTID}},
  {COMMAND_TYPE::SHOWNOTI , Typelist{}},
  {COMMAND_TYPE::SHOWSEENNOTI , Typelist{TYPE_NAME::LIMIT}},
  {COMMAND_TYPE::SHOWMONEY , Typelist{}}
  // {COMMAND_TYPE:: , Typelist{}}
};

map<COMMAND_TYPE, Typelist> command_optimal_list = {
  {COMMAND_TYPE::SIGNUP , Typelist{TYPE_NAME::ISPUB}},
  {COMMAND_TYPE::LOGIN , Typelist{}},
  {COMMAND_TYPE::LOGOUT , Typelist{}},
  {COMMAND_TYPE::POSTFILM , Typelist{}},
  {COMMAND_TYPE::EDITFILM , Typelist{TYPE_NAME::NAME,TYPE_NAME::YEAR,TYPE_NAME::LENGTH,
    TYPE_NAME::SUMMARY,TYPE_NAME::DIRECTOR}},
  {COMMAND_TYPE::DELETEFILM , Typelist{}},
  {COMMAND_TYPE::SHOWFOLOWERS , Typelist{}},
  {COMMAND_TYPE::GETPROFIT , Typelist{}},
  {COMMAND_TYPE::FOLLOW , Typelist{}},
  {COMMAND_TYPE::SEARCHPOSTED , Typelist{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::SEARCHFILMS , Typelist{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::SEARCHPURCHASED , Typelist{TYPE_NAME::NAME,TYPE_NAME::PRICE,TYPE_NAME::DIRECTOR,
    TYPE_NAME::RATE,TYPE_NAME::YEAR}},
  {COMMAND_TYPE::GETFILM , Typelist{}},
  {COMMAND_TYPE::ADDMONEY , Typelist{}},
  {COMMAND_TYPE::BUYFILM , Typelist{}},
  {COMMAND_TYPE::RATEFILM , Typelist{}},
  {COMMAND_TYPE::ADDCOMMENT , Typelist{}},
  {COMMAND_TYPE::REPLYCOMMENT , Typelist{}},
  {COMMAND_TYPE::DELETECOMMENT , Typelist{}},
  {COMMAND_TYPE::SHOWNOTI , Typelist{}},
  {COMMAND_TYPE::SHOWSEENNOTI , Typelist{}},
  {COMMAND_TYPE::SHOWMONEY , Typelist{}}
  // {COMMAND_TYPE:: , Typelist{}}
};

COMMAND_TYPE CommandHandler::get_command_type(vector<string> command, Parametrs input)
{
  if(command.size() == 0)
    throw Error(BAD_REQUEST_MSG);
  if(command[0]!="GET" && command[0]!="POST" && command[0]!="DELETE" && command[0]!="PUT")
    throw Error(BAD_REQUEST_MSG);
  vector<COMMAND_TYPE> ct, res;
  pair<string,string> method = {command[0],stick_strings(command)};
  for(auto u:command_method_cache)
    if(u.second == method)
      ct.push_back(u.first);
  if(ct.size() == 0)
    throw Error(NOT_FOUND_MSG);
  for(auto u:ct)
    if(check_validate(u, input))
      res.push_back(u);
  if(res.size() != 1)
    throw Error(BAD_REQUEST_MSG);
  return res[0];
}

string CommandHandler::stick_strings(vector<string> command)
{
  string met;
  for(int i=1;i<int(command.size());i++)
  {
    if(command[i] == SPLITER)
      break;
    if(i!=1)
      met += " ";
    met += command[i];
  }
  return met;
}

Parametrs CommandHandler::get_parametrs(vector<string> command)
{
  int ind=0;
  for(;ind<int(command.size());ind++)
    if(command[ind] == SPLITER)
      break;
  if(ind==int(command.size()))
    return Parametrs();
  ind++;
  if((command.size()-ind)%2 == 1)
    throw Error(BAD_REQUEST_MSG);
  Parametrs res;
  for(int i=ind;i<int(command.size());i+=2)
  {
    Component* new_cp = build_component(command[i],command[i+1]);
    if(new_cp == NULL || new_cp->validation() == false)
      throw Error(BAD_REQUEST_MSG);
    res.push_back(new_cp);
  }
  return res;
}

bool CommandHandler::check_validate(COMMAND_TYPE ctype, Parametrs params)
{
  Typelist primary_list = command_primary_list[ctype];
  Typelist optimal_list = command_optimal_list[ctype];

  if(!check_duplicate_params(params) ||
  !check_primary_existance_params(params, primary_list) ||
  !check_valid_params(params, primary_list, optimal_list))
    return false;
  return true;
}

bool CommandHandler::check_duplicate_params(Parametrs params)
{
  for(int i=0;i<int(params.size());i++)
    for(int j=i+1;j<int(params.size());j++)
      if(params[i]->get_type() == params[j]->get_type() && params[i]->get_filter_type() == params[j]->get_filter_type())
        return false;
  return true;
}

bool CommandHandler::check_primary_existance_params(Parametrs params, Typelist primary_list)
{
  for(auto& u:primary_list)
  {
    bool exist = false;
    for(auto& cp:params)
      exist |= (cp->get_type()==u);
    if(exist == false)
      return false;
  }
  return true;
}

bool CommandHandler::check_valid_params(Parametrs params,Typelist primary_list, Typelist optimal_list)
{
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
