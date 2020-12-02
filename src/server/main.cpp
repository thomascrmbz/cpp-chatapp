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
  for (auto user : users) if (user.get_connection() == connection) return user;
  throw "user_not_found";
}

ChatApp::User get_user(std::string username) {
  for (auto user : users) if (user.get_username() == username) return user;
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
      
      try {
        if (frame.get_opcode() == 0x03) users.push_back(ChatApp::User(trim_string(frame.get_payload()), connection));
        else if (frame.get_opcode() == 0x04) {
          std::string username = frame.get_payload().substr(0, frame.get_payload().find_first_of(";"));
          std::string message = trim_string(frame.get_payload()).substr(trim_string(frame.get_payload()).find_first_of(";") + 1, trim_string(frame.get_payload()).size() - 1);
          WebSocket::Frame f("private!" + get_user(connection).get_username() + ";" + message);
          f.set_opcode(0x04);
          get_user(username).get_connection()->write(f);
        } else {
          for (WebSocket::Connection * con : connections) {
            if (con->is_connected() && con != connection) con->write("global!" + get_user(connection).get_username() + ";" + trim_string(frame.get_payload()));
          }
        }
      } catch(const char * error) {}
    };

    connection->on_close = [connection]() {
      for (int i = 0; i < users.size(); i++) if (users[i].get_connection() == connection) users.erase(users.begin() + i);
    };
  };

  server.listen(3000);

  return 0;
}