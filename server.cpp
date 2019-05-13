
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
  users.push_back(new User(params));
}

void Server::add_film(std::vector<Component*> params)
{
  films.push_back(new Film(params));
}

void Server::edit_film(std::vector<Component*> params)
{
  Component* cid = NULL;
  for(auto& u:params)
    if(u->get_type() == TYPE_NAME::ID)
      cid = u;
  if(cid == NULL)
    throw Error("WTF");
  Entity* et = Filter_interface::find_exact(films, cid);
  if(et == NULL)
    throw Error("Not Found");
  for(auto& u:params)
    if(u->get_type() != TYPE_NAME::ID)
    {
      Component* cp = et->get_component22(u->get_type());
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
  // complete this later
  cout << "SHOW Followers Called! " << endl;
}

// User* guser = Filter_interface::find_exact(users,params[0]);
// vector<User*> glist = Filter_interface::filter_min(users,params[0]);
// guser->get_component<Name>(TYPE_NAME::USER_NAME)->edit_name(params[1]->get_value());
