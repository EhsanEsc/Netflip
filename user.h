
#ifndef USER_H
#define USER_H

#include "entity.h"

class Film;

class User : public Entity
{
public:
  User(std::vector<Component*> comps);
  void show();

  std::vector<User*> get_followers();
  bool is_publisher();
private:
  std::vector<User*> followers;
  std::vector<User*> following;
  // vector<Notification*> notis;
  std::vector<Film*> purchased;
  std::vector<Film*> posted;

  void add_optimal_attribute();
  int get_new_id();
};

#endif
