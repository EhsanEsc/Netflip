
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

void Server::show(std::vector<Component*> params)
{
  User* guser = Filter_interface::find_exact(users,params[0]);
  if(guser==NULL)
    cout << "User Not Found" << endl;
  else
    guser->show();
}
void Server::showmin(std::vector<Component*> params)
{
  vector<User*> glist = Filter_interface::filter_min(users,params[0]);
  cout << "##" << endl;
  for(auto& g:glist)
    g->show();
  cout << "##" << endl;
}
void Server::editname(std::vector<Component*> params)
{
  User* guser = Filter_interface::find_exact(users,params[0]);
  if(guser == NULL)
    cout << "User not found" << endl;
  else
  {
    cout << "#\n";
    cout << " Before => ";
    guser->show();
    guser->get_component<Name>(TYPE_NAME::USER_NAME)->edit_name(params[1]->get_value());
    cout << " After => ";
    guser->show();
    cout << "#\n";
  }
}
