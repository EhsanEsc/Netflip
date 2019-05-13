
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
  films.push_back(new_film);
}

void Server::edit_film(std::vector<Component*> params)
{
  Component* cid = NULL;
  for(auto& u:params)
    if(u->get_type() == TYPE_NAME::ID)
      cid = u;
  Film* fl = Filter_interface::find_exact(films, cid);
  if(fl == NULL)
    throw Error("Not Found");
  if(fl->get_publisher() != current_user)
    throw Error("Permision Denied");

  for(auto& u:params)
    if(u->get_type() != TYPE_NAME::ID)
    {
      Component* cp = fl->get_component22(u->get_type());
      cp = u;
    }
}

void Server::delete_film(std::vector<Component*> params)
{
  for(int i=0;i<films.size();i++)
  {
    if(films[i]->get_component<Number>(TYPE_NAME::ID)->get_value() == params[0]->get_value())
    {
      films.erase(films.begin()+i);
      return ;
    }
  }
  throw Error("Not Found");
}

void Server::show_followers(std::vector<Component*> params)
{
  vector<TYPE_NAME> format{TYPE_NAME::ID, TYPE_NAME::USER_NAME, TYPE_NAME::EMAIL};
  vector<User*> luser = current_user->get_followers();
  luser = Filter_interface::sort(luser, TYPE_NAME::ID);

  cout << "List of Followers" << endl;
  cout << "User Id | User Username | User Email" << endl;
  for(auto& u: luser)
  {
    for(int i=0;i<format.size();i++)
    {
      cout << u->get_component22(format[i])->get_value() ;
      if(i!=format.size()-1)
        cout << " | ";
    }
    cout << endl;
  }
}

void Server::get_money(std::vector<Component*> params)
{

}

// User* guser = Filter_interface::find_exact(users,params[0]);
// vector<User*> glist = Filter_interface::filter_min(users,params[0]);
// guser->get_component<Name>(TYPE_NAME::USER_NAME)->edit_name(params[1]->get_value());
