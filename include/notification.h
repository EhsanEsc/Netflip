
#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "entity.h"
#include <vector>

class Noti : public Entity
{
public:
  Noti(std::vector<Component*> params);
  void print();
private:
};

#endif