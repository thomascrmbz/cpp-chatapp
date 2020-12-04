#include "chat_ui.h"
#include "chat_server.h"

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

  chat_ui.on_command = [&](std::string command) {
  };

  chat_ui.on_message = [&](std::string message) {
    chat_server.write(message, 0x1);
  };

  chat_server.connect();

  while (!chat_server.is_connected()) ;

  chat_ui.run();

  return 0;
}