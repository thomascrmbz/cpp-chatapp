#include <iostream>

#include <websocket_client.h>
#include "chat_ui.h"

using namespace ChatApp;

int main() {
  ChatUI chatUI;

  std::cout << "Welcome to the C++ Chat App!" << std::endl;

  ChatServer chat_server = chatUI.get_chat_server();

  return 0;
}