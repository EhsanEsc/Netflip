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
private:
  static Server* instance;
  std::vector<User*> users;
};

#endif
