#pragma once

#include <string>
#include <functional>
#include <vector>

namespace ChatApp {

  class ChatUI {

    public:
      ChatUI(void);
      ~ChatUI();

    public:
      std::string ask_ip(void);
      std::string ask_username(void);

    public:
      void print_global_message(std::string username, std::string message);
      void print_private_message(std::string username, std::string message);
      void print_broadcast(std::string text);
      void print(std::string text);

    public:
      std::function<void(std::string, std::vector<std::string>)> on_command = [](std::string command, std::vector<std::string> args) {};
      std::function<void(std::string)> on_message = [](std::string message) {};

    public:
      void run(void);

    private:
      std::string ask(std::string message);
      void handle_command(std::string input);

    private:
      std::string current_input = "";
      std::string previous_input = "";
      std::string next_input = "";

  };

}