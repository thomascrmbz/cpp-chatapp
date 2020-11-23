#include <websocket_server.h>

#include <string>
#include <iostream>
#include <thread>
#include <chrono>


void fake_input(WebSocket::Connection * connection) {
  while (connection->is_connected()) {
    connection->write("Fake input");
    std::this_thread::sleep_for((std::chrono::seconds) 1);
  }
}

int main() {

  WebSocket::Server server;

  server.on_connection = [](WebSocket::Connection * connection) {
    connection->write("Hello World!");

    std::thread(fake_input, connection).detach();

    connection->on_message = [connection](std::string message) {
      std::cout << message << std::endl;
      connection->write("Default reply");
    };
  };

  server.listen(3000);

  return 0;
}