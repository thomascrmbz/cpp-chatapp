#include "chat_ui.h"

#include <iostream>
#include <string>

using namespace ChatApp;

ChatUI::ChatUI(void) {
  system("clear");
}

ChatUI::~ChatUI() {
  // system("clear");
}

ChatApp::ChatServer ChatUI::get_chat_server(void) {
  std::cout << "Server ip: ";
  std::string ip;
  std::cin >> ip;

  return ChatServer(ip);
}