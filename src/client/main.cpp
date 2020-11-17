#include <iostream>
#include <future>

#include <websocket_client.h>
#include "chat_ui.h"

using namespace ChatApp;

int main() {
  ChatUI chatUI;

  std::cout << "Welcome to the C++ Chat App!" << std::endl;

  ChatServer chat_server = chatUI.get_chat_server();

  std::future<void> input = std::async(std::launch::async, &ChatUI::update, &chatUI, &chat_server);

  std::cout << "main thread + ChatUI::update thread is now running" << std::endl;

  while(true) {
    chatUI.wait_for_chat_input();
    std::cout << "input: " << chatUI.get_input() << std::endl;
  }

  return 0;
}