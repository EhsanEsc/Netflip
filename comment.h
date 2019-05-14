
#ifndef COMMENT_H
#define COMMENT_H

#include "entity.h"

class Comment : public Entity
{
public:
  Comment(std::vector<Component*> comps, bool rep);
  Comment(int id,std::string content, bool rep);
  bool is_reply();
  void add_reply(Comment* cm);
  void print();
private:
  bool be_reply;
  std::vector<Comment*> replys;
};

#endif
