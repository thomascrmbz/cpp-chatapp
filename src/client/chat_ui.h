#pragma once

#include <string>

namespace ChatApp {

  class ChatUI {

    public:
      ChatUI(void);
      ~ChatUI();

    public:
      std::string get_input(void) const;
      std::string get_current_input(void) const;
      std::string ask_ip(void) const;
      bool is_command(void) const;

    public:
      void wait_for_chat_input(void);
      void show_input(void);
      void output(std::string message);

    private:
      std::string format_output(std::string message) const;
      std::string format_output(std::string username, std::string message) const;
      std::string format_input(void) const;
      void run_command(std::string command);

    private:
      std::string input;
      std::string current_input;
  };
}