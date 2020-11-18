#pragma once

#include "chat_server.h"

namespace ChatApp {

  class ChatUI {

    public:
      ChatUI(void);
      ~ChatUI();

    public:
      std::string get_input(void) const;
      std::string get_current_input(void) const;

    public:
      void wait_for_chat_input(void);
      void show_input(void);
      void update(ChatApp::ChatServer * chat_server);

    public:
      ChatApp::ChatServer get_chat_server(void);

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