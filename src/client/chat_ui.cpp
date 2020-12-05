#include "chat_ui.h"

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "helper.h"

using namespace ChatApp;

ChatUI::ChatUI(void) {
  system("clear");
}

ChatUI::~ChatUI() {
  system("clear");
}

std::string ChatUI::ask_ip(void) {
  return this->ask("Server ip:");
}

std::string ChatUI::ask_username(void) {
  return this->ask("Username:");
}

void ChatUI::print_global_message(std::string username, std::string message) {
  this->print("\e[90m" + username + "\e[0m: " + message);
}

void ChatUI::print_private_message(std::string username, std::string message) {
  this->print("\e[1;35mFrom \e[0m" + username + ": " + message);
}

void ChatUI::print_broadcast(std::string text) {
  this->print("\e[93m" + text);
}

void ChatUI::print(std::string text) {
  std::cout << "\n\e[2K\e[1A" << text << "\e[0m\n" << "> " << this->current_input;
  std::cout.flush();
}

void ChatUI::run(void) {
  std::cout << "\e[94m/help to show all available commands\e[0m" << std::endl;

  std::cout << "> ";
  std::cout.flush();

  while (true) {
    std::string input = "";

    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    
    int width = size.ws_col; // @todo fix message overflow

    while (true) {
      int c = Helper().getch();
      
      if (c == 27) {
        if (Helper().getch() == 91) {
          int x = Helper().getch();
          // @todo implement specific functions like edit previous message, go to left...
          if (x == 65) {
            printf("\e[1B");
            if (input != this->previous_input && this->previous_input.length() > 0) {
              this->next_input = input;
              input = this->previous_input;
              printf("\n\e[2K\e[1A> %s\e[0K", input.c_str());
            }
          }
          if (x == 66) {
            printf("\e[1A");
            if (input.length() > 0) {
              this->previous_input = input;
              input = this->next_input;
              this->next_input = "";
              printf("\n\e[2K\e[1A> %s\e[0K", input.c_str());
            }
          }
          if (x == 67) printf("\e[1D"); // right
          if (x == 68) printf("\e[1C"); // left
        }
      }
      else {
        if (c == 127) input = input.substr(0, input.length() - 1);
        else if (c != 10) input += (char) c;
        else {
          input = Helper().trim_string(input);
          if(input.length()) {
            printf("\e[1A\e[2K");
            break;
          }
          else printf("\e[1A\e[2C");
        }
      }

      if (c == 127) printf("\n\e[2K\e[1A> %s\e[0K", input.c_str());

      this->current_input = input;
    }

    this->current_input = "";
    this->previous_input = input;
    this->next_input = "";

    if (input[0] == '/') this->handle_command(input);
    else {
      this->print_global_message("\e[1;32myou", input);
      this->on_message(input);
    }
  }
}

std::string ChatUI::ask(std::string message) {
  std::string str;
  std::cout << message << " ";
  std::cin >> str;
  std::cin.ignore();

  return str;
}

void ChatUI::handle_command(std::string input) {
  std::string command = input.substr(1, input.find_first_of(' ') - 1);
  std::vector<std::string> command_list = { "exit", "help", "msg" };
  std::vector<std::string> args;
  if (input.size() > (command.size() + 2)) args = Helper::string_to_vector(input.substr(command.length() + 2, input.size() - 1));
  
  if (std::find(command_list.begin(), command_list.end(), command) != command_list.end()) this->on_command(command, args);
  else this->print("\e[1;31mThis command doesn\'t exist! Try /help.\e[0m");
}