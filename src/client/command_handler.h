#pragma once

#include "chat_server.h"
#include "chat_ui.h"

#include <string>
#include <vector>
#include <sstream>
#include <iterator>

namespace ChatApp {

  class CommandHandler {

    public:
      static void handle(std::string command, std::vector<std::string> args, ChatApp::ChatUI * chat_ui, ChatApp::ChatServer * chat_server) {
        if (command == "help") {
          chat_ui->print("\e[94m/help \e[0m- show all available commands");
          chat_ui->print("\e[94m/msg <username> <message> \e[0m- send a private message");
          // chat_ui->print("\e[94m/r <message> \e[0m- reply to a private message");
          chat_ui->print("\e[94m/exit \e[0m- exit the chat");
        }
        if (command == "msg" && args.size() > 1) {
          std::stringstream ss;
          std::copy(args.begin() + 1, args.end() - 1, std::ostream_iterator<std::string>(ss, " "));
          ss << args.back();

          std::string username = args[0];
          std::string message = ss.str();
          chat_server->write(username + ";" + message, 0x4);
          chat_ui->print("\e[1;35mTo \e[0m" + username + ": " + message);
        }
        if (command == "exit") exit(0);
      }

  };

}