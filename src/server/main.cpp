#include <websocket_server.h>

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

std::string trim_string(std::string str) {
  std::string s = "";
  for (char c : str) if (c != 0) s += c;
  return s;
}

int main() {

  WebSocket::Server server;

  server.set_debug(true);

  std::vector<WebSocket::Connection *> connections;

  server.on_connection = [&](WebSocket::Connection * connection) {
    connection->write("Hello World!");
    connections.push_back(connection);

    connection->on_message = [connection, connections](std::string message) {
      std::cout << message << std::endl;
      for (WebSocket::Connection * con : connections) {
        if (con->is_connected() && con != connection) con->write(trim_string(message));
      }
    };
  };

  server.listen(3000);

  return 0;
}