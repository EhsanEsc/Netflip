
#include "meserver.h"
#include "cp_headers.h"
#include "entity_headers.h"
#include "filter.h"
#include "notihandler.h"
#include "recomender.h"
#include<iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

MeServer::MeServer()
{
  noti_handler = NotiHandler::get_instance();
  filter = Filter::get_instance();
  recomender = Recomender::get_instance();

  admin = new User(Parametrs{
    new Number("0",TYPE_NAME::USERID),
    new Name("admin",TYPE_NAME::USER_NAME),
    new Password("admin",TYPE_NAME::PASSWORD),
    new Number("0",TYPE_NAME::MONEY)
  });
  users.push_back(admin);
}

MeServer* MeServer::instance = NULL;
MeServer* MeServer::get_instance()
{
  if(instance == NULL)
    instance = new MeServer();
  return instance;
}

void MeServer::check_validate(COMMAND_TYPE ct, Parametrs params)
{
  if(current_user != NULL)
    if(ct == COMMAND_TYPE::SIGNUP || ct == COMMAND_TYPE::LOGIN)
      throw Error(BAD_REQUEST_MSG);
  if(current_user == NULL)
    if(ct != COMMAND_TYPE::SIGNUP && ct != COMMAND_TYPE::LOGIN)
      throw Error(BAD_REQUEST_MSG);
  if(current_user != NULL && current_user->is_publisher() == false)
    if(ct == COMMAND_TYPE::POSTFILM || ct == COMMAND_TYPE::EDITFILM || ct == COMMAND_TYPE::DELETEFILM
    || ct == COMMAND_TYPE::GETPROFIT || ct == COMMAND_TYPE::SEARCHPOSTED || ct == COMMAND_TYPE::REPLYCOMMENT
    || ct == COMMAND_TYPE::DELETECOMMENT)
      throw Error(PERMISSION_DENIED_MSG);
  if(ct == COMMAND_TYPE::EDITFILM || ct == COMMAND_TYPE::DELETEFILM || ct == COMMAND_TYPE::GETFILM
    || ct == COMMAND_TYPE::BUYFILM || ct == COMMAND_TYPE::RATEFILM || ct == COMMAND_TYPE::ADDCOMMENT
    || ct == COMMAND_TYPE::REPLYCOMMENT || ct == COMMAND_TYPE::DELETECOMMENT)
  {
    Component* cid = filter->search(params, TYPE_NAME::FILMID);
    Film* fl = filter->find_exact(films, cid);
    if(fl == NULL)
      throw Error(NOT_FOUND_MSG);
  }
}

Respond MeServer::add_user(Parametrs params)
{
  Component* cid = filter->search(params, TYPE_NAME::USER_NAME);
  User* us = filter->find_exact(users,cid);
  if(us != NULL)
    throw Error("This username is already exist!");
  us = new User(params);
  if(us->is_ok() == false)
    throw Error(BAD_REQUEST_MSG);
  current_user = us;
  users.push_back(current_user);

  return SUCCESS_RESPOND;
}

Respond MeServer::add_film(Parametrs params)
{
  Film* new_film = new Film(params, current_user);
  if(new_film->is_ok() == false)
    throw Error(BAD_REQUEST_MSG);
  current_user->add_posted_film(new_film);
  films.push_back(new_film);

  send_noti_new_film(current_user);
  int fid = new_film->get_component<Number>(TYPE_NAME::FILMID)->get();
  recomender->add_node(fid);

  return SUCCESS_RESPOND;
}

Respond MeServer::edit_film(Parametrs params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  Film* fl = filter->find_exact(films, cid);
  if(fl->get_publisher() != current_user)
    throw Error(PERMISSION_DENIED_MSG);
  for(auto& u:params)
    if(u->get_type() != TYPE_NAME ::FILMID)
    {
      Component* cp = fl->get_component_bytype(u->get_type());
      cp->edit(u->get_value());
    }

  return SUCCESS_RESPOND;
}

Respond MeServer::delete_film(Parametrs params)
{
  for(int i=0;i<int(films.size());i++)
  {
    if(*films[i]->get_component<Number>(TYPE_NAME::FILMID) == *params[0])
    {
      if(films[i]->get_publisher() != current_user)
        throw Error(PERMISSION_DENIED_MSG);
      recomender->delete_node(films[i]->get_component<Number>(TYPE_NAME::FILMID)->get());
      films.erase(films.begin()+i);

      return SUCCESS_RESPOND;
    }
  }
}

Respond MeServer::show_followers(Parametrs params)
{
  Typelist format{TYPE_NAME::USERID, TYPE_NAME::USER_NAME, TYPE_NAME::EMAIL};
  vector<User*> luser = current_user->get_followers();
  luser = filter->sort(luser, TYPE_NAME::USERID);

  string title = "#. User Id | User Username | User Email";
  return print_entities(title, transform_to_entity(luser), format);
}

Respond MeServer::get_profit(Parametrs params)
{
  for(auto& fl : current_user->get_posted_films())
    fl->pay_publisher(admin);
  return SUCCESS_RESPOND;
}

Respond MeServer::add_money(Parametrs params)
{
  current_user->charge_account(stoi(params[0]->get_value()));
  return SUCCESS_RESPOND;
}

Respond MeServer::follow_user(Parametrs params)
{
  User* us = filter->find_exact(users, params[0]);
  if(us == NULL)
    throw Error(NOT_FOUND_MSG);
  if(us->is_publisher() == false)
    throw Error(BAD_REQUEST_MSG);

  send_noti_follow_user(current_user, us);

  User* rr = filter->find_exact(us->get_followers(), current_user->get_component_bytype(TYPE_NAME::USERID));
  if(rr != NULL)
    return NULL_RESPOND;

  current_user->follow(us);
  us->add_follower(current_user);
  return SUCCESS_RESPOND;
}

Respond MeServer::login(Parametrs params)
{
  Name* username = filter->search_exact<Name>(params, TYPE_NAME::USER_NAME);
  Password* pass = filter->search_exact<Password>(params, TYPE_NAME::PASSWORD);

  User* us = filter->find_exact(users,username);
  if(us == NULL)
    throw Error(NOT_FOUND_MSG);

  if(*us->get_component<Password>(TYPE_NAME::PASSWORD) == *pass)
    current_user = us;
  else
    throw Error(BAD_REQUEST_MSG);
  return SUCCESS_RESPOND;
}

Respond MeServer::logout(Parametrs params)
{
  if(current_user == NULL)
    throw Error(BAD_REQUEST_MSG);
  current_user = NULL;
  return SUCCESS_RESPOND;
}

Respond MeServer::show_posted_films(Parametrs params)
{
  return show_films(current_user->get_posted_films(), params);
}

Respond MeServer::show_all_films(Parametrs params)
{
  return show_films(films, params);
}

Respond MeServer::show_purchased_films(Parametrs params)
{
  return show_films(current_user->get_purchased_films(), params);
}

Respond MeServer::show_film_detail(Parametrs params)
{
  Film* fl = filter->find_exact(films, params[0]);
  Respond res;

  stringstream ss;
  ss << "Details of Film " << fl->get_component<Name>(TYPE_NAME::NAME)->get_value() << endl;
  res.push_back(ss.str()); ss.str(" ");
  Respond tmp = fl->print_details();
  res.insert(res.end(), tmp.begin(), tmp.end());

  ss << "Comments" << endl;
  res.push_back(ss.str()); ss.str(" ");
  tmp = fl->print_comments();
  res.insert(res.end(), tmp.begin(), tmp.end());

  ss << "Recommendation Film" << endl;
  res.push_back(ss.str()); ss.str(" ");
  tmp = show_reccomendation_films(current_user,fl);
  res.insert(res.end(), tmp.begin(), tmp.end());

  return res;
}

Respond MeServer::print_entities(string title, vector<Entity*> list, Typelist format)
{
  vector<string> res;
  res.push_back(title);
  for(int j=0;j<int(list.size());j++)
  {
    stringstream ss;
    ss << j+1 << ". ";
    for(int i=0;i<int(format.size());i++)
    {
      ss << list[j]->get_component_bytype(format[i])->get_value() ;
      if(i+1<int(format.size()))
        ss << " | ";
    }
    res.push_back(ss.str());
  }
  return res;
}

Respond MeServer::show_films(std::vector<Film*>list, Parametrs params)
{
  for(auto& u:params)
    list = filter->filter(list, u);
  list = filter->sort(list, TYPE_NAME::FILMID);
  Typelist format{TYPE_NAME::FILMID, TYPE_NAME::NAME, TYPE_NAME::LENGTH, TYPE_NAME::PRICE,
    TYPE_NAME::FILMRATE, TYPE_NAME::YEAR, TYPE_NAME::DIRECTOR};
  string title = "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director";
  return print_entities(title, transform_to_entity(list) , format);
}

Respond MeServer::show_reccomendation_films(User* us, Film* fl)
{
  vector<int> restricted_film_ids = get_film_ids(us->get_purchased_films());
  vector<int> best_ids = recomender->get_recomend_ids(fl->get_id(), restricted_film_ids);

  vector<Film*> res;
  for(auto& u: best_ids)
    for(auto& f : films)
      if(f->get_id() == u)
        res.push_back(f);

  Typelist format = {TYPE_NAME::FILMID, TYPE_NAME::NAME, TYPE_NAME::LENGTH, TYPE_NAME::DIRECTOR};
  string title = "#. Film Id | Film Name | Film Length | Film Director";
  return print_entities(title, transform_to_entity(res), format);
}

Respond MeServer::buy_film(Parametrs params)
{
  Film* fl = filter->find_exact(films, params[0]);

  if(filter->find_exact(current_user->get_purchased_films(),
  fl->get_component_bytype(TYPE_NAME::FILMID)) == NULL)
  {
    vector<int> purchased_film_ids = get_film_ids(current_user->get_purchased_films());
    recomender->add_weight(fl->get_id(), purchased_film_ids);

    current_user->buy_film(fl, admin);
    send_noti_film(current_user, fl , NOTI_TYPE::BUYFILM);
  }
  return SUCCESS_RESPOND;
}

Respond MeServer::rate_film(Parametrs params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  int score = filter->search_exact<Number>(params, TYPE_NAME::RATE)->get();
  if(score > 10 || score < 1)
    throw Error(BAD_REQUEST_MSG);
  Film* fl = filter->find_exact(films, cid);
  if(current_user->is_purchased(fl) == false)
    throw Error(PERMISSION_DENIED_MSG);

  int pre_score = current_user->get_rate(fl);
  if(pre_score != -1)
    fl->get_component<Vint>(TYPE_NAME::FILMRATE)->pop(pre_score);
  fl->get_component<Vint>(TYPE_NAME::FILMRATE)->push(score);
  current_user->add_rate(fl, score);

  send_noti_film(current_user, fl , NOTI_TYPE::RATEFILM);
  return SUCCESS_RESPOND;
}

Respond MeServer::add_comment(Parametrs params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  string content = filter->search(params, TYPE_NAME::CONTENT)->get_value();
  Film* fl = filter->find_exact(films, cid);
  if(current_user->is_purchased(fl) == false)
    throw Error(PERMISSION_DENIED_MSG);
  fl->add_comment(content, current_user);

  send_noti_film(current_user, fl , NOTI_TYPE::COMMENT);
  return SUCCESS_RESPOND;
}

Respond MeServer::reply_comment(Parametrs params)
{
  Component* cid = filter->search(params, TYPE_NAME::FILMID);
  string content = filter->search(params, TYPE_NAME::CONTENT)->get_value();
  Component* cmid = filter->search(params, TYPE_NAME::COMMENTID);
  Film* fl = filter->find_exact(films, cid);
  if(fl->get_publisher() != current_user)
    throw Error(PERMISSION_DENIED_MSG);
  fl->reply_comment(cmid,content);

  User* wr = fl->get_comment_writer(cmid);
  send_noti_reply_comment(current_user, wr);
  return SUCCESS_RESPOND;
}

Respond MeServer::delete_comment(Parametrs params)
{
  Component* cfid = filter->search(params, TYPE_NAME::FILMID);
  Component* cmid = filter->search(params, TYPE_NAME::COMMENTID);
  Film* fl = filter->find_exact(films, cfid);
  if(fl->get_publisher() != current_user)
    throw Error(PERMISSION_DENIED_MSG);
  fl->delete_comment(cmid);
  return SUCCESS_RESPOND;
}

Respond MeServer::show_notis(Parametrs params)
{
  // Maybe fix this later;
  current_user->show_notis();
  return SUCCESS_RESPOND;
}

Respond MeServer::show_seen_notis(Parametrs params)
{
  int limit = filter->search_exact<Number>(params, TYPE_NAME::LIMIT)->get();
  current_user->show_seen_notis(limit);
  return SUCCESS_RESPOND;
}

Respond MeServer::show_money(Parametrs params)
{
  return Respond{current_user->get_component<Number>(TYPE_NAME::MONEY)->get()};
}

pair<std::string,std::string> MeServer::get_info(User* us)
{
    pair<string,string> p;
    p.first = us->get_component_bytype(TYPE_NAME::USER_NAME)->get_value();
    p.second = us->get_component_bytype(TYPE_NAME::USERID)->get_value();
    return p;
}

pair<std::string,std::string> MeServer::get_info(Film* fl)
{
  pair<string,string> p;
  p.first = fl->get_component_bytype(TYPE_NAME::NAME)->get_value();
  p.second = fl->get_component_bytype(TYPE_NAME::FILMID)->get_value();
  return p;
}

void MeServer::send_noti_new_film(User* user)
{
  pair<string,string> ps = get_info(user);
  for(auto& u:current_user->get_followers())
    noti_handler->add_noti(u,NOTI_TYPE::REGISTERFILM,vector<string>{ps.first, ps.second});
}

void MeServer::send_noti_follow_user(User* us1, User* us2)
{
  pair<string,string> ps = get_info(us1);
  noti_handler->add_noti(us2,NOTI_TYPE::FOLLOW,vector<string>{ps.first, ps.second});
}

void MeServer::send_noti_film(User* user, Film* fl , NOTI_TYPE nt)
{
  pair<string,string> ps = get_info(current_user);
  pair<string,string> pf = get_info(fl);
  vector<string> info{ps.first, ps.second, pf.first, pf.second};
  noti_handler->add_noti(fl->get_publisher(),nt,info);
}

void MeServer::send_noti_reply_comment(User* user, User* wr)
{
  pair<string,string> ps = get_info(user);
  noti_handler->add_noti(wr,NOTI_TYPE::REPLYCOMMENT,{ps.first, ps.second});
}

std::vector<Entity*> MeServer::transform_to_entity(std::vector<Film*> flist)
{
  vector<Entity*> res;
  for(auto& u: flist)
    res.push_back(u);
  return res;
}

std::vector<Entity*> MeServer::transform_to_entity(std::vector<User*> ulist)
{
  vector<Entity*> res;
  for(auto& u: ulist)
    res.push_back(u);
  return res;
}

vector<Film*> MeServer::sort_samerate_films_byid(vector<Film*> list)
{
  vector<Film*> res;
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
  return res;
}

std::vector<int> MeServer::get_film_ids(std::vector<Film*> list)
{
  vector<int> res;
  for(auto& u: list)
    res.push_back(u->get_component<Number>(TYPE_NAME::FILMID)->get());
  return res;
}
