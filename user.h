
#ifndef USER_H
#define USER_H

#include "entity.h"

class User : public Entity
{
public:
  User(std::vector<Component*> comps);
private:
  int get_new_id();
};

#endif
