
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include<vector>
#include<string>
#include "sources.h"

class Component;

class CommandHandler
{
public:
  static CommandHandler* get_instance();
  void run();
private:
  static CommandHandler* instance;

  std::vector<std::string> split_line(std::string line);
  COMMAND_TYPE get_command_type(std::vector<std::string> command, std::vector<Component*> input);
  std::vector<Component*> get_parametrs(std::vector<std::string> command);

  bool check_validate(COMMAND_TYPE ctype, std::vector<Component*> params);
};

#endif
