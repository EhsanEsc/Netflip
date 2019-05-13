
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

// User* guser = Filter_interface::find_exact(users,params[0]);
// vector<User*> glist = Filter_interface::filter_min(users,params[0]);
// guser->get_component<Name>(TYPE_NAME::USER_NAME)->edit_name(params[1]->get_value());
