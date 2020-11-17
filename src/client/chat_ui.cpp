#include "chat_ui.h"

#include <iostream>
#include <string>
#include <future>
#include <chrono>

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
  std::cin.ignore();

  return ChatServer(ip);
}

void ChatUI::wait_for_chat_input(void) {
  std::cout << "> ";
  std::cout.flush();
  std::string input;
  do {
    std::getline(std::cin, input);
  } while (input.length() == 0);
  this->input = input;
}

void ChatUI::update(ChatApp::ChatServer * chat_server) {
  while(true) {
    std::this_thread::sleep_for((std::chrono::milliseconds) 2000);
    printf("\033[1A");

    time_t now = time(0);
    std::cout << "\nnew message" << "\n> ";
    std::cout.flush();
  }
}

std::string ChatUI::get_input(void) const {
  return this->input;
}