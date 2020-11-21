#include <iostream>
#include <future>

#include <websocket_client.h>
#include "chat_ui.h"
#include "chat_server.h"

using namespace ChatApp;

int main() {
  ChatUI chatUI;
  std::cout << "Welcome to the C++ Chat App!" << std::endl;

  ChatServer chat_server(chatUI.ask_ip(), &chatUI);

  std::cout << "/help to show all available commands" << std::endl;

  while(true) {
    chatUI.wait_for_chat_input();
    chatUI.show_input();
    if (!chatUI.is_command()) chat_server.send(chatUI.get_input());
  }

  return 0;
}