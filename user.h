
#ifndef USER_H
#define USER_H

#include "entity.h"

class Film;

class User : public Entity
{
public:
  User(std::vector<Component*> comps);
  void show();

  void add_posted_film(Film* fl);
  void add_money(int gold);

  std::vector<User*> get_followers();
  std::vector<Film*> get_posted_films();
  bool is_publisher();
private:
  std::vector<User*> followers;
  std::vector<User*> following;
  // vector<Notification*> notis;
  std::vector<Film*> purchased_films;
  std::vector<Film*> posted_films;

  void add_optimal_attribute();
  int get_new_id();
};

#endif
