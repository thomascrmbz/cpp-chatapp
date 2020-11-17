#pragma once

#include "chat_server.h"

namespace ChatApp {

  class ChatUI {

    public:
      ChatUI(void);
      ~ChatUI();

    public:
      ChatApp::ChatServer get_chat_server(void);

  };
}