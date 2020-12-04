#pragma once

#include <string>
#include <functional>
#include <websocket_client.h>

namespace ChatApp {

  class ChatServer {

    public:
      ChatServer(std::string ip);
      ~ChatServer();

    public:
      void set_username(std::string username);

    public:
      void connect(void);
      void write(std::string message, int type);
      bool is_connected(void);

    public:
      std::function<void(std::string, std::string, int)> on_message = [](std::string username, std::string message, int type) {};

    private:
      void listen(void);

    private:
      std::string ip;
      std::string username;
      WebSocket::Connection * connection;
      bool connected = false;

  };

}