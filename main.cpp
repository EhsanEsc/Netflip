
#include "command_handler.h"

using namespace std;

int main()
{
  freopen("in.txt","r",stdin);

  CommandHandler* handler = CommandHandler::get_instance();
  handler->run();

  return 0;
}
