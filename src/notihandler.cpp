
#include "notihandler.h"
#include "user.h"
#include "notification.h"
using namespace std;

map<NOTI_TYPE,int> noti_size_cache = {
  {NOTI_TYPE::REPLYCOMMENT,2},
  {NOTI_TYPE::REGISTERFILM,2},
  {NOTI_TYPE::FOLLOW,2},
  {NOTI_TYPE::BUYFILM,4},
  {NOTI_TYPE::RATEFILM,4},
  {NOTI_TYPE::COMMENT,4}
};

NotiHandler* NotiHandler::instance = NULL;
NotiHandler* NotiHandler::get_instance()
{
  if(instance == NULL)
    instance = new NotiHandler();
  return instance;
}

void NotiHandler::add_noti(User* user, NOTI_TYPE nt, std::vector<string> input)
{
  if(int(input.size()) != noti_size_cache[nt])
    throw Error(WIERD_ERROR_MSG);
  string msg;
  if(nt == NOTI_TYPE::REPLYCOMMENT) {
    msg = "Publisher " + input[0] + " with id " + input[1] + " reply to your comment.";
  } else if(nt == NOTI_TYPE::REGISTERFILM) {
    msg = "Publisher " + input[0] + " with id " + input[1] + " register new film.";
  } else if(nt == NOTI_TYPE::FOLLOW) {
    msg = "User " + input[0] + " with id " + input[1] + " follow you.";
  } else if(nt == NOTI_TYPE::BUYFILM) {
    msg = "User " + input[0] + " with id " + input[1] + " buy your film " + input[2] + " with id " + input[3] + ".";
  } else if(nt == NOTI_TYPE::RATEFILM) {
    msg = "User " + input[0] + " with id " + input[1] + " rate your film " + input[2] + " with id " + input[3] + ".";
  } else if(nt == NOTI_TYPE::COMMENT) {
    msg = "User " + input[0] + " with id " + input[1] + " comment on your film " + input[2] + " with id " + input[3] + ".";
  }

  Noti* new_noti = new Noti(Parametrs{new Name(msg,TYPE_NAME::CONTENT)});
  user->add_noti(new_noti);
}
