#include "chat_ui.h"

#include <iostream>
#include <string>

#include "helper.h"

using namespace ChatApp;

ChatUI::ChatUI(void) {
  system("clear");
}

ChatUI::~ChatUI() {
  system("clear");
}

ChatApp::ChatServer ChatUI::get_chat_server(void) {
  std::cout << "Server ip: ";
  std::string ip;
  std::cin >> ip;
  std::cin.ignore();

  return ChatServer(ip);
}

// http://www.climagic.org/mirrors/VT100_Escape_Codes.html
void ChatUI::wait_for_chat_input(void) {
  std::cout << "> ";
  std::cout.flush();

  std::string str = "";

  while(true) {
    int c = Helper().getch();

    if (c == 27) {
      if (Helper().getch() == 91) {
        int x = Helper().getch();
        // @todo implement specific functions like edit previous message, go to left...
        if (x == 65) printf("\033[1B"); // up
        if (x == 66) printf("\033[1A"); // down
        if (x == 67) printf("\033[1D"); // right
        if (x == 68) printf("\033[1C"); // left
      }
    } else {
      if (c != 10) str += (char) c;
      else {
        str = Helper().trim_string(str);
        if(str.length()) {
          printf("\033[1A\033[2K");
          break;
        }
        else printf("\033[1A\033[2C");
      }
      
      if (c == 127) str = str.substr(0, str.length() - 2);
    }

    if (c == 127) printf("\n\033[2K\033[1A> %s\033[K", str.c_str());

    this->current_input = str;
  }

  this->input = str;
  this->current_input = "";
}

void ChatUI::update(ChatApp::ChatServer * chat_server) {
  while(true) {
    std::string message = chat_server->wait_and_get_message();
    std::cout << "\n\033[2K\033[1A       fake_user \033[0m\033[1;31m|\033[0m \033[90m" << message << "\033[0m\033[K\n> " << this->get_current_input();
    std::cout.flush();
  }
}

void ChatUI::show_input(void) {
  std::string input = this->get_input();
  if (input == "/help") {
    std::cout << "                 \033[0m\033[1;90m|\033[0m " << "\033[94m/help \033[0m- show all available commands" << std::endl;
    std::cout << "                 \033[0m\033[1;90m|\033[0m " << "\033[94m/exit \033[0m- exit the chat" << std::endl;
  }
  else if (input == "/exit") {
    std::cout << "                 \033[0m\033[1;90m|\033[0m " << "Exiting..." << std::endl;
    exit(0);
  }
  else std::cout << "\033[1;32m             you \033[0m\033[1;31m|\033[0m " << input << std::endl;
}

std::string ChatUI::get_input(void) const {
  return this->input;
}

std::string ChatUI::get_current_input(void) const {
  return this->current_input;
}