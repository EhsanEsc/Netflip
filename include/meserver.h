#ifndef MeServer_H
#define MeServer_H

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
class Recomender;

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

typedef std::vector<std::string> Respond;
const Respond SUCCESS_RESPOND = std::vector<std::string>{"OK"};
const Respond FAIL_RESPOND = std::vector<std::string>{"FAIL"};
const Respond NULL_RESPOND = std::vector<std::string>{};

class MeServer
{
public:
  MeServer();
  static MeServer* get_instance();

  Respond add_user(Parametrs params);
  Respond add_film(Parametrs params);
  Respond edit_film(Parametrs params);
  Respond delete_film(Parametrs params);
  Respond show_followers(Parametrs params);
  Respond get_profit(Parametrs params);
  Respond follow_user(Parametrs params);
  Respond login(Parametrs params);
  Respond logout(Parametrs params);
  Respond show_posted_films(Parametrs params);
  Respond show_all_films(Parametrs params);
  Respond show_purchased_films(Parametrs params);
  Respond show_film_detail(Parametrs params);
  Respond add_money(Parametrs params);
  Respond buy_film(Parametrs params);
  Respond rate_film(Parametrs params);
  Respond add_comment(Parametrs params);
  Respond reply_comment(Parametrs params);
  Respond delete_comment(Parametrs params);
  Respond show_notis(Parametrs params);
  Respond show_seen_notis(Parametrs params);
  Respond show_money(Parametrs params);

  void check_validate(COMMAND_TYPE ct, Parametrs params);
private:
  static MeServer* instance;
  NotiHandler* noti_handler;
  Filter* filter;
  Recomender* recomender;
  std::vector<User*> users;
  std::vector<Film*> films;
  User* current_user=NULL;
  User* admin = NULL;

  Respond show_films(std::vector<Film*> list, Parametrs params);
  Respond show_reccomendation_films(User* us, Film* fl);
  Respond print_entities(std::string title, std::vector<Entity*> list, Typelist format);
  void send_noti_new_film(User* user);
  void send_noti_follow_user(User* us1, User* us2);
  void send_noti_film(User* user, Film* fl , NOTI_TYPE nt);
  void send_noti_reply_comment(User* user, User* wr);

  std::pair<std::string,std::string> get_info(User* us);
  std::pair<std::string,std::string> get_info(Film* us);
  std::vector<Entity*>transform_to_entity(std::vector<Film*> flist);
  std::vector<Entity*>transform_to_entity(std::vector<User*> ulist);
  std::vector<Film*> sort_samerate_films_byid(std::vector<Film*> list);
  std::vector<int> get_film_ids(std::vector<Film*> list);
};

#endif
