
#ifndef FILM_H
#define FILM_H

#include "entity.h"

class User;

class Film : public Entity
{
public:
  Film(std::vector<Component*> params);

private:
  User* publisher;
  // vector<Comment*> comments;

  int get_new_id();
};

#endif
