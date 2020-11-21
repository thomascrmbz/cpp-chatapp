#include <websocket_server.h>

#include <string>
#include <iostream>
#include <thread>
#include <chrono>


void fake_input(WebSocket::Connection * connection) {
  while (true) {
    uint8_t buffer[] = { 0x81, 0x0A, 'F', 'a', 'k', 'e', ' ', 'i', 'n', 'p', 'u', 't' };
    connection->write(buffer, sizeof(buffer));
    std::this_thread::sleep_for((std::chrono::seconds) 1);
  }
}

int main() {

  WebSocket::Server server;

  server.on_connection = [](WebSocket::Connection * connection) {
    uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    connection->write(buffer, sizeof(buffer));

    std::thread(fake_input, connection).detach();

    connection->on_message = [connection](std::string message) {
      std::cout << message << std::endl;
      uint8_t buffer[] = { 0x81, 0x0D, 'D', 'e', 'f', 'a', 'u', 'l', 't', ' ', 'r', 'e', 'p', 'l', 'y' };
      connection->write(buffer, sizeof(buffer));
    };
  };

  server.listen(3000);

  return 0;
}