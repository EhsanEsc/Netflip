
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include<vector>
#include<string>
#include "error.h"
#include "meserver.h"

class Component;

class CommandHandler
{
public:
  static CommandHandler* get_instance();
  Respond run_command(std::string line);
private:
  static CommandHandler* instance;

  std::vector<std::string> split_line(std::string line);
  COMMAND_TYPE get_command_type(std::vector<std::string> command, Parametrs input);
  Parametrs get_parametrs(std::vector<std::string> command);

  bool check_validate(COMMAND_TYPE ctype, Parametrs params);

  std::string stick_strings(std::vector<std::string> command);
  bool check_duplicate_params(Parametrs params);
  bool check_primary_existance_params(Parametrs params, Typelist primary_list);
  bool check_valid_params(Parametrs params, Typelist primary_list, Typelist optimal_list);
};

#endif
