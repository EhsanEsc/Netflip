
#ifndef SORCES_H
#define SORCES_H

#include<string>

constexpr int INF = 1e7+22;
constexpr int MAX_CNT_COMPONENT = 22;

enum class TYPE_NAME
{
  FILMID,
  USERID,
  COMMENTID,
  NOTIID,
  USER_NAME,
  EMAIL,
  PASSWORD,
  AGE,
  ISPUB,
  NAME,
  YEAR,
  LENGTH,
  PRICE,
  SUMMARY,
  DIRECTOR,
  FILMRATE,
  MONEY,
  RATE,
  CONTENT,
  LIMIT,
  UNDEFINED
};
TYPE_NAME get_type_name(std::string key);

class Error
{
public:
  Error(std::string str);
  std::string what();
private:
  std::string msg;
};

class Component;
Component* build_component(std::string key,std::string value);
Component* build_component(TYPE_NAME tn, std::string value);

enum class FILTER_TYPE
{
  EXACT,
  MIN,
  MAX,
  UNDEFINED
};

enum class COMMAND_TYPE
{
  SIGNUP,
  LOGIN,
  POSTFILM,
  EDITFILM,
  DELETEFILM,
  SHOWFOLOWERS,
  GETPROFIT,
  FOLLOW,
  SEARCHPOSTED,
  SEARCHFILMS,
  SEARCHPURCHASED,
  GETFILM,
  ADDMONEY,
  BUYFILM,
  RATEFILM,
  ADDCOMMENT,
  REPLYCOMMENT,
  DELETECOMMENT,
  SHOWNOTI,
  SHOWSEENNOTI,
  UNDEFINED
};

#endif
