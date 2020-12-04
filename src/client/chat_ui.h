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

    public:
      std::function<void()> on_command = []() {};
      std::function<void(std::string)> on_message = [](std::string message) {};

    public:
      void loop(void);
      void clear(void);

    private:
      void print(std::string text);

    private:
      void render(void);

    private:
      int width = 0;
      int height = 0;
      std::vector<std::vector<char>> screen;

  };

}