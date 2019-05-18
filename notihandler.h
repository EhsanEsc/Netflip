
#ifndef NOTIHANDLER_H
#define NOTIHANDLER_H

#include "sources.h"
#include <vector>
#include <string>
class User;

enum class NOTI_TYPE
{
  REPLYCOMMENT,
  REGISTERFILM,
  FOLLOW,
  BUYFILM,
  RATEFILM,
  COMMENT
};

class NotiHandler
{
public:
  static NotiHandler* get_instance();
  void add_noti(User* user, NOTI_TYPE nt, std::vector<std::string> input);
private:
  static NotiHandler* instance;
};

#endif
