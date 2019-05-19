
#include "command_handler.h"

using namespace std;

int main()
{
  CommandHandler* handler = CommandHandler::get_instance();
  handler->run();

  return 0;
}
