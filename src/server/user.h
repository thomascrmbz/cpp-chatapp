#pragma once

#include <string>
#include <websocket_server.h>

namespace ChatApp {
  class User {

    public:
      User(std::string username, WebSocket::Connection * connection);

    public:
      std::string get_username(void);
      WebSocket::Connection * get_connection(void);

    private:
      std::string username;
      WebSocket::Connection * connection;
  };
}