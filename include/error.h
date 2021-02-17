
#ifndef SORCES_H
#define SORCES_H

#include<string>

constexpr int INF = 1e7+22;
constexpr int MAX_CNT_COMPONENT = 22;
constexpr int MAX_CNT_FILMS = 1e3+22;

const std::string SUCCESS_COMMAND_MSG = "OK";
const std::string NOT_FOUND_MSG = "Not Found";
const std::string BAD_REQUEST_MSG = "Bad Request";
const std::string PERMISSION_DENIED_MSG = "Permission Denied";
const std::string WIERD_ERROR_MSG = "Holala :|";

class Error
{
public:
  Error(std::string str);
  std::string what();
private:
  std::string msg;
};

#endif
