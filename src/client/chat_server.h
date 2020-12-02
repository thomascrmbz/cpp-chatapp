#pragma once

#include <string>

#include <websocket_client.h>

#include "chat_ui.h"

namespace ChatApp {

  class ChatServer {

    public:
      ChatServer(std::string ip, ChatApp::ChatUI * chatUI, std::string username);
      ~ChatServer();
      
    public:
      void send(std::string message);

    private:
      void listen(void);

    private:
      std::string ip;
      ChatApp::ChatUI * chatUI;
      WebSocket::Connection * ws_connection;
      std::string username;
  };
}