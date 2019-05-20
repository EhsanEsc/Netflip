#ifndef SERVER_H
#define SERVER_H

#include "error.h"
#include "component.h"
#include "notihandler.h"
#include<vector>
#include<string>
#include <utility>

class Entity;
class User;
class Film;
class Component;
class NotiHandler;
class Filter;

enum class COMMAND_TYPE
{
  SIGNUP,
  LOGIN,
  LOGOUT,
  POSTFILM,
  EDITFILM,
  DELETEFILM,
  SHOWFOLOWERS,
  GETPROFIT,
  FOLLOW,
  SEARCHPOSTED,
  SEARCHFILMS,
  SEARCHPURCHASED,
  GETFILM,
  ADDMONEY,
  BUYFILM,
  RATEFILM,
  ADDCOMMENT,
  REPLYCOMMENT,
  DELETECOMMENT,
  SHOWNOTI,
  SHOWSEENNOTI,
  SHOWMONEY,
  UNDEFINED
};

class Server
{
public:
  Server();
  static Server* get_instance();

  void add_user(Parametrs params);
  void add_film(Parametrs params);
  void edit_film(Parametrs params);
  void delete_film(Parametrs params);
  void show_followers(Parametrs params);
  void get_profit(Parametrs params);
  void follow_user(Parametrs params);
  void login(Parametrs params);
  void logout(Parametrs params);
  void show_posted_films(Parametrs params);
  void show_all_films(Parametrs params);
  void show_purchased_films(Parametrs params);
  void show_film_detail(Parametrs params);
  void add_money(Parametrs params);
  void buy_film(Parametrs params);
  void rate_film(Parametrs params);
  void add_comment(Parametrs params);
  void reply_comment(Parametrs params);
  void delete_comment(Parametrs params);
  void show_notis(Parametrs params);
  void show_seen_notis(Parametrs params);
  void show_money(Parametrs params);

  void check_validate(COMMAND_TYPE ct, Parametrs params);
private:
  static Server* instance;
  NotiHandler* noti_handler;
  Filter* filter;
  std::vector<User*> users;
  std::vector<Film*> films;
  User* current_user=NULL;
  User* admin = NULL;

  void show_films(std::vector<Film*> list, Parametrs params);
  void show_reccomendation_films(User* us, Film* fl);
  void print_entities(std::string title, std::vector<Entity*> list, Typelist format);
  void send_noti_new_film(User* user);
  void send_noti_follow_user(User* us1, User* us2);
  void send_noti_film(User* user, Film* fl , NOTI_TYPE nt);
  void send_noti_reply_comment(User* user, User* wr);

  std::pair<std::string,std::string> get_info(User* us);
  std::pair<std::string,std::string> get_info(Film* us);
  std::vector<Entity*>transform_to_entity(std::vector<Film*> flist);
  std::vector<Entity*>transform_to_entity(std::vector<User*> ulist);
  std::vector<Film*> sort_samerate_films_byid(std::vector<Film*> list);

};

#endif
