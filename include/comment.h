
#ifndef COMMENT_H
#define COMMENT_H

#include "entity.h"

class User;

class Comment : public Entity
{
public:
  Comment(Parametrs comps, bool rep, User* wr);
  Comment(int id,std::string content, bool rep,User* wr);

  User* get_writer();
  bool is_reply();
  void add_reply(Comment* cm);
  std::string print();
  int get_new_reply_comment_id();
private:
  User* writer;
  std::vector<Comment*> replys;
  bool be_reply;
  int last_reply_comment_id = 0;
};

#endif
