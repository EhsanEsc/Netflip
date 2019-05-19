
#include "server.h"
#include "cp_headers.h"
#include "entity_headers.h"
#include "filter.h"
#include "notihandler.h"
#include<iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

Server::Server()
{
  noti_handler = NotiHandler::get_instance();
  filter = Filter::get_instance();
  cout << setprecision(2);
}

Server* Server::instance = NULL;
Server* Server::get_instance()
{
  if(instance == NULL)
    instance = new Server();
  return instance;
}

void Server::check_validate(COMMAND_TYPE ct, std::vector<Component*> params)
{
  if(current_user == NULL)
    if(ct != COMMAND_TYPE::SIGNUP && ct != COMMAND_TYPE::LOGIN)
      throw Error("Permission Denied");
  if(current_user != NULL && current_user->is_publisher() == false)
    if(ct == COMMAND_TYPE::POSTFILM || ct == COMMAND_TYPE::EDITFILM || ct == COMMAND_TYPE::DELETEFILM
    || ct == COMMAND_TYPE::GETPROFIT || ct == COMMAND_TYPE::SEARCHPOSTED || ct == COMMAND_TYPE::REPLYCOMMENT
    || ct == COMMAND_TYPE::DELETECOMMENT)
      throw Error("Permission Denied");
  if(ct == COMMAND_TYPE::EDITFILM || ct == COMMAND_TYPE::DELETEFILM || ct == COMMAND_TYPE::GETFILM
    || ct == COMMAND_TYPE::BUYFILM || ct == COMMAND_TYPE::RATEFILM || ct == COMMAND_TYPE::ADDCOMMENT
    || ct == COMMAND_TYPE::REPLYCOMMENT || ct == COMMAND_TYPE::DELETECOMMENT)
  {
    Component* cid = filter->search(params, TYPE_NAME::FILMID);
    Film* fl = filter->find_exact(films, cid);
    if(fl == NULL)
      throw Error("Not Found");
  }
}

void Server::add_user(std::vector<Component*> params)
{
  Component* cid = filter->search(params, TYPE_NAME::USER_NAME);
  User* us = filter->find_exact(users,cid);
  if(us != NULL)
    throw Error("Bad Request");
  current_user = new User(params);
  users.push_back(current_user);
}

void Server::add_film(std::vector<Component*> params)
{
  Film* new_film = new Film(params, current_user);
  current_user->add_posted_film(new_film);
  films.push_back(new_film);

  pair<string,string> ps = get_info(current_user);
  vector<string> info{ps.first, ps.second};
  for(auto& u:current_user->get_followers())
    noti_handler->add_noti(u,NOTI_TYPE::REGISTERFILM,info);
}

void Server::edit_film(std::vector<Component*> params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  Film* fl = filter->find_exact(films, cid);
  if(fl->get_publisher() != current_user)
    throw Error("Permission Denied");
  for(auto& u:params)
    if(u->get_type() != TYPE_NAME::FILMID)
    {
      Component* cp = fl->get_component22(u->get_type());
      cp->edit(u->get_value());
    }
}

void Server::delete_film(std::vector<Component*> params)
{
  for(int i=0;i<int(films.size());i++)
  {
    if(films[i]->get_component<Number>(TYPE_NAME::FILMID)->get_value() == params[0]->get_value())
    {
      if(films[i]->get_publisher() != current_user)
        throw Error("Permission Denied");
      films.erase(films.begin()+i);
      return ;
    }
  }
}

void Server::show_followers(std::vector<Component*> params)
{
  vector<TYPE_NAME> format{TYPE_NAME::USERID, TYPE_NAME::USER_NAME, TYPE_NAME::EMAIL};
  vector<User*> luser = current_user->get_followers();
  luser = filter->sort(luser, TYPE_NAME::USERID);

  cout << "List of Followers" << endl;
  cout << "#. User Id | User Username | User Email" << endl;
  for(int j=0;j<int(luser.size());j++)
  {
    User* u = luser[j];
    cout << j+1 << ". ";
    for(int i=0;i<int(format.size());i++)
    {
      cout << u->get_component22(format[i])->get_value() ;
      if(i!=int(format.size())-1)
        cout << " | ";
    }
    cout << endl;
  }
}

void Server::get_profit(std::vector<Component*> params)
{
  for(auto& fl : current_user->get_posted_films())
    fl->pay_publisher();
}

void Server::add_money(std::vector<Component*> params)
{
  current_user->get_component<Number>(TYPE_NAME::MONEY)->add(stoi(params[0]->get_value()));
}

void Server::follow_user(std::vector<Component*> params)
{
  User* us = filter->find_exact(users, params[0]);
  if(us->is_publisher() == false)
    throw Error("Bad Request");

  pair<string,string> ps = get_info(current_user);
  vector<string> info{ps.first, ps.second};
  noti_handler->add_noti(us,NOTI_TYPE::FOLLOW,info);

  User* rr = filter->find_exact(us->get_followers(), current_user->get_component22(TYPE_NAME::USERID));
  if(rr != NULL)
    return;

  current_user->follow(us);
  us->add_follower(current_user);
}

void Server::login(std::vector<Component*> params)
{
  Name* username = filter->search_exact<Name>(params, TYPE_NAME::USER_NAME);
  Password* pass = filter->search_exact<Password>(params, TYPE_NAME::PASSWORD);

  if(username == NULL || pass == NULL)
    throw Error("WTF");
  for(auto& u:users)
  {
    if(u->get_component<Name>(TYPE_NAME::USER_NAME)->get_value() == username->get_value())
    {
      if(u->get_component<Password>(TYPE_NAME::PASSWORD)->get_value() == pass->get_value())
      {
        current_user = u;
        return;
      }
      throw Error("Bad Request");
    }
  }
  throw Error("Not Found");
}

void Server::show_posted_films(std::vector<Component*> params)
{
  show_films(current_user->get_posted_films(), params);
}

void Server::show_all_films(std::vector<Component*> params)
{
  show_films(films, params);
}

void Server::show_purchased_films(std::vector<Component*> params)
{
  show_films(current_user->get_purchased_films(), params);
}

void Server::show_film_detail(std::vector<Component*> params)
{
  Film* fl = filter->find_exact(films, params[0]);

  cout << "Details of Film " << fl->get_component<Name>(TYPE_NAME::NAME)->get_value() << endl;
  fl->print_details();
  cout << endl;

  cout << "Comments" << endl;
  fl->print_comments();
  cout << endl;

  cout << "Recommendation Film" << endl;
  show_reccomendation_films(current_user,fl);
}

void Server::print_films(string title, vector<Film*> list, vector<TYPE_NAME> format)
{
  cout << title << endl;
  for(int j=0;j<int(list.size());j++)
  {
    Film* fl = list[j];
    cout << j+1 << ". ";
    for(int i=0;i<int(format.size());i++)
    {
      cout << fl->get_component22(format[i])->get_value() ;
      if(i+1<int(format.size()))
        cout << " | ";
    }
    cout << endl;
  }
}

void Server::show_films(std::vector<Film*>list, std::vector<Component*> params)
{
  for(auto& u:params)
    list = filter->filter(list, u);
  list = filter->sort(list, TYPE_NAME::FILMID);
  vector<TYPE_NAME>format{TYPE_NAME::FILMID, TYPE_NAME::NAME, TYPE_NAME::LENGTH, TYPE_NAME::PRICE,
    TYPE_NAME::FILMRATE, TYPE_NAME::YEAR, TYPE_NAME::DIRECTOR};
  string title = "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director";
  print_films(title, list, format);
}

void Server::show_reccomendation_films(User* us, Film* fl)
{
  vector<Film*> list, res;
  for(auto& u: films)
    if(us->is_purchased(u) == false && u!=fl)
      list.push_back(u);
  list = filter->sort(list, TYPE_NAME::FILMRATE);
  reverse(list.begin(),list.end());
  for(int i=0;i<int(list.size());i++)
  {
    vector<Film*> tmp;
    double rt = list[i]->get_component<Vint>(TYPE_NAME::FILMRATE)->get_average();
    int j=i;
    while(j<int(list.size()) && rt==list[j]->get_component<Vint>(TYPE_NAME::FILMRATE)->get_average())
    { j++; }
    for(int k=i;k<j;k++)
      tmp.push_back(list[k]);
    tmp = filter->sort(tmp, TYPE_NAME::FILMID);

    for(auto& u:tmp)
      res.push_back(u);
    i=j-1;
  }

  vector<TYPE_NAME> format = {TYPE_NAME::FILMID, TYPE_NAME::NAME, TYPE_NAME::LENGTH, TYPE_NAME::DIRECTOR};
  string title = "#. Film Id | Film Name | Film Length | Film Director";
  if(res.size() > 4)
    res.resize(4);
  print_films(title, res, format);
}

void Server::buy_film(std::vector<Component*> params)
{
  Film* fl = filter->find_exact(films, params[0]);

  pair<string,string> ps = get_info(current_user);
  pair<string,string> pf = get_info(fl);
  vector<string> info{ps.first, ps.second, pf.first, pf.second};
  noti_handler->add_noti(fl->get_publisher(),NOTI_TYPE::BUYFILM,info);

  if(filter->find_exact(current_user->get_purchased_films(),
    fl->get_component22(TYPE_NAME::FILMID)) != NULL)
      return;
  current_user->buy_film(fl);
}

void Server::rate_film(std::vector<Component*> params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  int score = stoi(filter->search(params, TYPE_NAME::RATE)->get_value());
  if(score > 10 || score < 1)
    throw Error("Bad Request");
  Film* fl = filter->find_exact(films, cid);
  if(current_user->is_purchased(fl) == false)
    throw Error("Permission Denied");
  int pre_score = current_user->get_rate(fl);
  if(pre_score != -1)
    fl->get_component<Vint>(TYPE_NAME::FILMRATE)->pop(pre_score);
  fl->get_component<Vint>(TYPE_NAME::FILMRATE)->push(score);
  current_user->add_rate(fl, score);

  pair<string,string> ps = get_info(current_user);
  pair<string,string> pf = get_info(fl);
  vector<string> info{ps.first, ps.second, pf.first, pf.second};
  noti_handler->add_noti(fl->get_publisher(),NOTI_TYPE::RATEFILM,info);
}

void Server::add_comment(std::vector<Component*> params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  string content = filter->search(params, TYPE_NAME::CONTENT)->get_value();
  Film* fl = filter->find_exact(films, cid);
  if(current_user->is_purchased(fl) == false)
    throw Error("Permission Denied");
  fl->add_comment(content, current_user);

  pair<string,string> ps = get_info(current_user);
  pair<string,string> pf = get_info(fl);
  vector<string> info{ps.first, ps.second, pf.first, pf.second};
  noti_handler->add_noti(fl->get_publisher(),NOTI_TYPE::COMMENT,info);
}

void Server::reply_comment(std::vector<Component*> params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  string content = filter->search(params, TYPE_NAME::CONTENT)->get_value();
  Component* cmid = filter->search(params, TYPE_NAME::COMMENTID);
  Film* fl = filter->find_exact(films, cid);
  if(fl->get_publisher() != current_user)
    throw Error("Permission Denied");
  fl->reply_comment(cmid,content);

  User* wr = fl->get_comment_writer(cmid);
  pair<string,string> ps = get_info(current_user);
  vector<string> info{ps.first, ps.second};
  noti_handler->add_noti(wr,NOTI_TYPE::REPLYCOMMENT,info);
}

void Server::delete_comment(std::vector<Component*> params)
{
  Component* cfid = filter->search(params, TYPE_NAME::FILMID);
  Component* cmid = filter->search(params, TYPE_NAME::COMMENTID);
  Film* fl = filter->find_exact(films, cfid);
  if(fl->get_publisher() != current_user)
    throw Error("Permission Denied");
  fl->delete_comment(cmid);
}

void Server::show_notis(std::vector<Component*> params)
{
  current_user->show_notis();
}

void Server::show_seen_notis(std::vector<Component*> params)
{
  int limit = stoi(filter->search(params, TYPE_NAME::LIMIT)->get_value());
  current_user->show_seen_notis(limit);
}

pair<std::string,std::string> Server::get_info(User* us)
{
    pair<string,string> p;
    p.first = us->get_component22(TYPE_NAME::USER_NAME)->get_value();
    p.second = us->get_component22(TYPE_NAME::USERID)->get_value();
    return p;
}

pair<std::string,std::string> Server::get_info(Film* us)
{
  pair<string,string> p;
  p.first = us->get_component22(TYPE_NAME::NAME)->get_value();
  p.second = us->get_component22(TYPE_NAME::FILMID)->get_value();
  return p;
}
