
#ifndef USER_H
#define USER_H

#include "entity.h"

class Film;
class Noti;

class User : public Entity
{
public:
  User(std::vector<Component*> comps);
  void show();

  void add_posted_film(Film* fl);
  void add_money(int gold);
  void follow(User* us);
  void add_follower(User* us);
  void buy_film(Film* fl);
  void add_noti(Noti* nt);
  void show_notis();
  void show_seen_notis(int limit);

  std::vector<User*> get_followers();
  std::vector<Film*> get_posted_films();
  std::vector<Film*> get_purchased_films();
  bool is_publisher();
  bool is_purchased(Film* fl);
private:
  std::vector<User*> followers;
  std::vector<User*> following;
  std::vector<Noti*> unread_notis;
  std::vector<Noti*> seen_notis;
  std::vector<Film*> purchased_films;
  std::vector<Film*> posted_films;

  void add_optimal_attribute();
  int get_new_id();
};

#endif
