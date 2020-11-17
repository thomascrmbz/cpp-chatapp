#pragma once

#include "chat_server.h"

namespace ChatApp {

  class ChatUI {

    public:
      ChatUI(void);
      ~ChatUI();

    public:
      std::string get_input(void) const;

    public:
      void wait_for_chat_input(void);
      void update(ChatApp::ChatServer * chat_server);

    public:
      ChatApp::ChatServer get_chat_server(void);

    private:
      std::string input;

  };
}