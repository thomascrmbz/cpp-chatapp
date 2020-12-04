#include <websocket_server.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "user.h"

std::string trim_string(std::string str) {
  std::string s = "";
  for (char c : str) if (c != 0) s += c;
  return s;
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
        if (frame.get_opcode() == 0x3) {
          ChatApp::User::add_user(ChatApp::User(trim_string(frame.get_payload()), connection));

          for (WebSocket::Connection * con : connections) {
            WebSocket::Frame f("broadcast!" + trim_string(frame.get_payload()) + ";joined");
            f.set_opcode(0xB);
            if (con->is_connected() && con != connection) con->write(f);
          }
        }
        else if (frame.get_opcode() == 0x4) {
          std::string username = frame.get_payload().substr(0, frame.get_payload().find_first_of(";"));
          std::string message = trim_string(frame.get_payload()).substr(trim_string(frame.get_payload()).find_first_of(";") + 1, trim_string(frame.get_payload()).size() - 1);

          WebSocket::Frame f("private!" + ChatApp::User::get_user(connection)->get_username() + ";" + message);
          f.set_opcode(0x4);
          
          ChatApp::User::get_user(username)->get_connection()->write(f);
        }
        else {
          for (WebSocket::Connection * con : connections) {
            if (con->is_connected() && con != connection) con->write("global!" + ChatApp::User::get_user(connection)->get_username() + ";" + trim_string(frame.get_payload()));
          }
        }
      } catch(const char * error) {}
    };

    connection->on_close = [connection]() {
      for (WebSocket::Connection * con : connections) {
        WebSocket::Frame frame("broadcast!" + ChatApp::User::get_user(connection)->get_username() + ";left");
        frame.set_opcode(0xB);
        if (con->is_connected() && con != connection) con->write(frame);
      }
      ChatApp::User::delete_user(connection);
    };
  };

  server.listen(3000);

  return 0;
}