
#ifndef FILM_H
#define FILM_H

#include "entity.h"

class User;
class Comment;

class Film : public Entity
{
public:
  Film(std::vector<Component*> params, User* _publisher);
  User* get_publisher();
  void pay_publisher();
  void print_details();
  void print_comments();
  void add_comment(std::string content, User* writer);
  void reply_comment(Component* cmid, std::string content);
  void delete_comment(Component* cmid);
  User* get_comment_writer(Component* cmid);
private:
  User* publisher;
  std::vector<Comment*> comments;
  int last_comment_id = 0;

  int get_new_id();
  int get_new_comment_id();
  int calc_paid_money(int profit);
};

#endif
