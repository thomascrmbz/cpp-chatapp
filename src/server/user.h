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

    public:
      static ChatApp::User * get_user(WebSocket::Connection * connection);
      static ChatApp::User * get_user(std::string username);
      static void add_user(ChatApp::User user);
      static void delete_user(WebSocket::Connection * connection);

    private:
      std::string username;
      WebSocket::Connection * connection;
  };

  static std::vector<ChatApp::User> users;

}