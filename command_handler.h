
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "sources.h"
#include "cp_headers.h"
#include "server.h"

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
  SEARCHPOSTED
};

class CommandHandler
{
public:
  static CommandHandler* get_instance();
  void run();
private:
  static CommandHandler* instance;

  std::vector<string> split_line(string line);
  COMMAND_TYPE get_command_type(std::vector<std::string> command);
  std::vector<Component*> get_parametrs(std::vector<std::string> command);

  bool check_validate(COMMAND_TYPE ctype, std::vector<Component*> params);
  // Component* build_component(std::string key,std::string value);
  void remove_input(std::vector<Component*> input);
};

#endif
