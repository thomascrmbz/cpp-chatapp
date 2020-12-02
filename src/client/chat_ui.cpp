#include "chat_ui.h"

#include <iostream>

#include "helper.h"

using namespace ChatApp;

ChatUI::ChatUI(void) {
  system("clear");
}

ChatUI::~ChatUI() {
  std::cout << "Exiting..." << std::endl;
  exit(0);
}

std::string ChatUI::ask_ip(void) const {
  std::cout << "Server ip: ";
  std::string ip;
  std::cin >> ip;
  std::cin.ignore();

  return ip;
}

std::string ChatUI::ask_username(void) const {
  std::cout << "Username: ";
  std::string username;
  std::cin >> username;
  std::cin.ignore();

  return username;
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

    if (c == 127) printf("\n\033[2K\033[1A> %s\033[0K", str.c_str());

    this->current_input = str;
  }

  this->input = str;
  this->current_input = "";
}

// void ChatUI::update(ChatApp::ChatServer * chat_server) {
//   // while(true) {
//   //   std::string message = chat_server->wait_and_get_message();
//     std::cout << "\n\033[2K\033[1A" << this->format_output("\033[90mfake_user", message) << "\033[0m\033[K\n> " << this->get_current_input();
//     std::cout.flush();
//   // }
// }

void ChatUI::output(std::string username, std::string message) {
  std::cout << "\n\033[2K\033[1A" << this->format_output("\033[90m" + username, message) << "\033[0m\033[K\n> " << this->get_current_input();
  std::cout.flush();
}

void ChatUI::output(std::string text) {
  std::cout << "\n\033[2K\033[1A\e[2K" << text << "\033[0m\033[K\n> " << this->get_current_input();
  std::cout.flush();
}

void ChatUI::show_input(void) {
  std::string input = this->get_input();
  if (input[0] == '/') this->run_command(input);
  else std::cout << this->format_output("\033[1;32myou", "\033[97m" + input) << std::endl;
}

bool ChatUI::is_command(void) const {
  return this->get_input()[0] == '/';
}

// https://misc.flogisoft.com/bash/tip_colors_and_formatting
void ChatUI::run_command(std::string command) {
  if (command == "/help") {
    std::cout << "\033[94m/help \033[0m- show all available commands" << std::endl;
    std::cout << "\033[94m/msg <username> <message> \033[0m- send a private message" << std::endl;
    std::cout << "\033[94m/r <message> \033[0m- reply to a private message" << std::endl;
    std::cout << "\033[94m/exit \033[0m- exit the chat" << std::endl;
  }
  else if (command == "/exit") delete this;
  else if (command.substr(0, 5) == "/msg " && (command.find_first_of(" ") != command.find_last_of(" "))) {
    std::string username = command.substr(5, command.substr(6, command.size() - 1).find_first_of(" ") + 1);
    std::string message =  command.substr(5 + username.size() + 1, command.size() - 1);
    std::cout << "\033[1;35mTo \033[0m" + username + "\033[97m:\033[90m " + message + "\033[0m" << std::endl;
    this->input = "private!" + username + ";" + message;
  }
  else if (command == "/play hangman") {
    std::cout << "\033[94mCongrats on finding an easter-egg!\e[0m" << std::endl;
    this->input = "minigame!hangman;start";
  }
  else if (command == "/play card") {
    std::cout << "\033[94mCongrats on finding an easter-egg!\e[0m" << std::endl;
    this->input = "minigame!card;start";
  }
  else std::cout << "\033[1;31mThis command doesn\'t exist! Try /help.\033[0m" << std::endl;
}

std::string ChatUI::format_output(std::string message) const {
  return this->format_output("", message);
}

std::string ChatUI::format_output(std::string username, std::string message) const {
  return username + "\033[0m\033[97m:\033[0m " + message + "\033[0m";
}

std::string ChatUI::format_input(void) const {
  return "";
}

std::string ChatUI::get_input(void) const {
  return this->input;
}

std::string ChatUI::get_current_input(void) const {
  return this->current_input;
}