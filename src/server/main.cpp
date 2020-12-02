#include <websocket_server.h>

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#include "user.h"

static std::vector<ChatApp::User> users;

std::string trim_string(std::string str) {
  std::string s = "";
  for (char c : str) if (c != 0) s += c;
  return s;
}

ChatApp::User get_user(WebSocket::Connection * connection) {
  for (auto user : users) {
    if (user.get_connection() == connection) return user;
  }
  throw "user_not_found";
}

int main() {

  WebSocket::Server server;

  server.set_debug(true);

  static std::vector<WebSocket::Connection *> connections;

  server.on_connection = [&](WebSocket::Connection * connection) {
    connections.push_back(connection);

    connection->on_message = [connection](WebSocket::Frame frame) {
      std::cout << frame.get_payload() << std::endl;
      
      if (frame.get_opcode() == 0x03) {
        users.push_back(ChatApp::User(trim_string(frame.get_payload()), connection));
        return;
      }

      for (WebSocket::Connection * con : connections) {
        if (con->is_connected() && con != connection) con->write(get_user(connection).get_username() + ";" + trim_string(frame.get_payload()));
      }
    };
  };

  server.listen(3000);

  return 0;
}