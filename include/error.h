
#ifndef SORCES_H
#define SORCES_H

#include<string>

constexpr int INF = 1e7+22;
constexpr int MAX_CNT_COMPONENT = 22;
constexpr int MAX_CNT_FILMS = 1e3+22;

class Error
{
public:
  Error(std::string str);
  std::string what();
private:
  std::string msg;
};

#endif
