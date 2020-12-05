#include "chat_ui.h"
#include "chat_server.h"
#include <sstream>
#include <iterator>

using namespace ChatApp;

int main() {
  ChatUI chat_ui;
  ChatServer chat_server(chat_ui.ask_ip());

  chat_server.set_username(chat_ui.ask_username());

  chat_server.on_message = [&](std::string username, std::string message, int type) {
    if (type == 0x1) chat_ui.print_global_message(username, message);
    if (type == 0x4) chat_ui.print_private_message(username, message);
    if (type == 0xB) chat_ui.print_broadcast(username + " has " + message + " the chat.");
  };

  chat_ui.on_command = [&](std::string command, std::vector<std::string> args) {
    // @todo move to a command handler
    if (command == "help") {
      chat_ui.print("\e[94m/help \e[0m- show all available commands");
      chat_ui.print("\e[94m/msg <username> <message> \e[0m- send a private message");
      // chat_ui.print("\e[94m/r <message> \e[0m- reply to a private message");
      chat_ui.print("\e[94m/exit \e[0m- exit the chat");
    }
    if (command == "msg" && args.size() > 1) {
      std::stringstream ss;
      std::copy(args.begin() + 1, args.end() - 1, std::ostream_iterator<std::string>(ss, " "));
      ss << args.back();

      std::string username = args[0];
      std::string message = ss.str();
      chat_server.write(username + ";" + message, 0x4);
      chat_ui.print("\e[1;35mTo \e[0m" + username + ": " + message);
    }
    if (command == "exit") exit(0);
  };

  chat_ui.on_message = [&](std::string message) {
    chat_server.write(message, 0x1);
  };

  chat_server.connect();

  while (!chat_server.is_connected()) ;

  chat_ui.run();

  return 0;
}