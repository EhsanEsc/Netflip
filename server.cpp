
#include "server.h"
using namespace std;

Server* Server::instance = NULL;
Server* Server::get_instance()
{
  if(instance == NULL)
    instance = new Server();
  return instance;
}

void Server::add_user(std::vector<Component*> params)
{
  Component* cid = Filter_interface::search(params, TYPE_NAME::USER_NAME);
  User* us = Filter_interface::find_exact(users,cid);
  if(us != NULL)
    throw Error("Bad Request");
  current_user = new User(params);
  users.push_back(current_user);
}

void Server::add_film(std::vector<Component*> params)
{
  if(current_user == NULL)
    throw Error("WTF");
  if(current_user->is_publisher() == false)
    throw Error("Permision Denied");
  Film* new_film = new Film(params, current_user);
  current_user->add_posted_film(new_film);
  films.push_back(new_film);
}

void Server::edit_film(std::vector<Component*> params)
{
  Component* cid = Filter_interface::search(params, TYPE_NAME::FILMID);
  Film* fl = Filter_interface::find_exact(films, cid);
  if(fl == NULL)
    throw Error("Not Found");
  if(fl->get_publisher() != current_user)
    throw Error("Permision Denied");

  for(auto& u:params)
    if(u->get_type() != TYPE_NAME::FILMID)
    {
      Component* cp = fl->get_component22(u->get_type());
      cp = u;
    }
}

void Server::delete_film(std::vector<Component*> params)
{
  if(current_user->is_publisher() == false)
    throw Error("Permision Denied");
  for(int i=0;i<films.size();i++)
  {
    if(films[i]->get_component<Number>(TYPE_NAME::FILMID)->get_value() == params[0]->get_value())
    {
      if(films[i]->get_publisher() != current_user)
        throw Error("Permision Denied");
      films.erase(films.begin()+i);
      return ;
    }
  }
  throw Error("Not Found");
}

void Server::show_followers(std::vector<Component*> params)
{
  vector<TYPE_NAME> format{TYPE_NAME::USERID, TYPE_NAME::USER_NAME, TYPE_NAME::EMAIL};
  vector<User*> luser = current_user->get_followers();
  luser = Filter_interface::sort(luser, TYPE_NAME::USERID);

  cout << "List of Followers" << endl;
  cout << "#. User Id | User Username | User Email" << endl;
  for(int j=0;j<luser.size();j++)
  {
    User* u = luser[j];
    cout << j+1 << ". ";
    for(int i=0;i<format.size();i++)
    {
      cout << u->get_component22(format[i])->get_value() ;
      if(i!=format.size()-1)
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
  User* us = Filter_interface::find_exact(users, params[0]);
  if(us->is_publisher() == false)
    throw Error("Bad Request");
  current_user->follow(us);
  us->add_follower(current_user);
}

void Server::login(std::vector<Component*> params)
{
  Name* username = Filter_interface::search_exact<Name>(params, TYPE_NAME::USER_NAME);
  Password* pass = Filter_interface::search_exact<Password>(params, TYPE_NAME::PASSWORD);

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
  if(current_user->is_publisher() == false)
    throw Error("Permision Denied");
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
  Film* fl = Filter_interface::find_exact(films, params[0]);
  if(fl == NULL)
    throw Error("Not Found");
  fl->print_details();
  cout << endl;
  fl->print_comments();
  // add recomendation
}

void Server::show_films(std::vector<Film*>list, std::vector<Component*> params)
{
  for(auto& u:params)
  {
    list = Filter_interface::filter(list, u);
  }
  list = Filter_interface::sort(list, TYPE_NAME::USERID);

  // maybe add function later
  vector<TYPE_NAME>format{TYPE_NAME::FILMID, TYPE_NAME::NAME, TYPE_NAME::LENGTH, TYPE_NAME::PRICE,
    TYPE_NAME::RATE, TYPE_NAME::YEAR, TYPE_NAME::DIRECTOR};
  cout << "#. Film Id | Film Name | Film Length | Film price | rate | Production Year | Film Director" << endl;
  for(int j=0;j<list.size();j++)
  {
    Film* fl = list[j];
    cout << j+1 << ". ";
    for(int i=0;i<format.size();i++)
    {
      cout << fl->get_component22(format[i])->get_value() ;
      if(i+1<format.size())
        cout << " | ";
    }
    cout << endl;
  }
}

void Server::buy_film(std::vector<Component*> params)
{
  Film* fl = Filter_interface::find_exact(films, params[0]);
  if(fl == NULL)
    throw Error("Not Found");
  current_user->buy_film(fl);
}

void Server::rate_film(std::vector<Component*> params)
{
  Component* cid = Filter_interface::search(params, TYPE_NAME::FILMID);
  int score = stoi(Filter_interface::search(params, TYPE_NAME::RATE)->get_value());
  if(score > 10 || score < 1)
    throw Error("Bad Request");
  Film* fl = Filter_interface::find_exact(films, cid);
  if(fl == NULL)
    throw Error("Not found");
  if(current_user->is_purchased(fl) == false)
    throw Error("Bad Request");
  fl->get_component<Number>(TYPE_NAME::RATE)->push(score);
}

void Server::add_comment(std::vector<Component*> params)
{
  // cout << "#" << endl;
  Component* cid = Filter_interface::search(params, TYPE_NAME::FILMID);
  // cout << "@" << endl;
  string content = Filter_interface::search(params, TYPE_NAME::CONTENT)->get_value();
  Film* fl = Filter_interface::find_exact(films, cid);
  if(fl == NULL)
    throw Error("Not Found");
  if(current_user->is_purchased(fl) == false)
    throw Error("Permision Denied");
  fl->add_comment(content);
}

void Server::reply_comment(std::vector<Component*> params)
{
  // Component* cid = find();
  // Film* fl = Filter_interface::find_exact(films, cid);
  // if(fl == NULL)
  //   throw Error("Not Found");
  // if(fl->get_publisher() != current_user)
  //   throw Error("Permision Denied");
  // fl->reply_comment(stoi(cid->get_value()),content);
}

// User* guser = Filter_interface::find_exact(users,params[0]);
// vector<User*> glist = Filter_interface::filter_min(users,params[0]);
// guser->get_component<Name>(TYPE_NAME::USER_NAME)->edit_name(params[1]->get_value());
