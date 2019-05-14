#ifndef SERVER_H
#define SERVER_H

#include "sources.h"
#include "cp_headers.h"
#include "entity_headers.h"
#include "filter.h"

class Server
{
public:
  static Server* get_instance();

  void add_user(std::vector<Component*> params);
  void add_film(std::vector<Component*> params);
  void edit_film(std::vector<Component*> params);
  void delete_film(std::vector<Component*> params);
  void show_followers(std::vector<Component*> params);
  void get_profit(std::vector<Component*> params);
  void follow_user(std::vector<Component*> params);
  void login(std::vector<Component*> params);
  void show_posted_films(std::vector<Component*> params);
  void show_all_films(std::vector<Component*> params);
  void show_purchased_films(std::vector<Component*> params);
  void show_film_detail(std::vector<Component*> params);
  void add_money(std::vector<Component*> params);
  void buy_film(std::vector<Component*> params);
  void rate_film(std::vector<Component*> params);
  void add_comment(std::vector<Component*> params);
  void reply_comment(std::vector<Component*> params);

private:
  static Server* instance;
  std::vector<User*> users;
  std::vector<Film*> films;
  User* current_user=NULL;

  void show_films(std::vector<Film*> list, std::vector<Component*> params);
};

#endif
