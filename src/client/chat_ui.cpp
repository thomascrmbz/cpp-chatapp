#include "chat_ui.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace ChatApp;

ChatUI::ChatUI(void) {
  // std::thread(&ChatUI::render, this).detach();
}

ChatUI::~ChatUI() {
  system("clear");
}

std::string ChatUI::ask_ip(void) {
  return "localhost";
}

std::string ChatUI::ask_username(void) {
  return "username";
}

void ChatUI::print_global_message(std::string username, std::string message) {
  this->print(username + ": " + message);
}

void ChatUI::print_private_message(std::string username, std::string message) {
  this->print("\e[1;35mFrom \e[0m" + username + " " + message);
}

void ChatUI::print(std::string text) {
  std::cout << text << std::endl;
}

void ChatUI::loop(void) {
  while (true) {
    std::string input = "";
    std::cin >> input;
    std::cin.ignore();
    std::cin.clear();

    this->on_message(input);
  }
}

void ChatUI::clear(void) {
  screen.clear();
  for (int x = 0; x < this->width; x++) {
    std::vector<char> ys;
    for (int y = 0; y < this->height; y++) {
      ys.push_back(' ');
    }
    screen.push_back(ys);
  }
}

void ChatUI::render(void) {
  while (true) {
    system("clear");
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    
    this->width = size.ws_col;
    this->height = size.ws_row;

    clear();

    for (int y = 0; y < this->height; y++) {
      for (int x = 0; x < this->width; x++) {
        std::cout << screen[x][y];
      }
      if (y + 1 < this->height) std::cout << std::endl;
      else std::cout.flush();
    }

    std::this_thread::sleep_for((std::chrono::milliseconds) 1000);
  }
}