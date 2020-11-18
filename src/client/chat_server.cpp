#include "chat_server.h"

#include <future>
#include <chrono>

using namespace ChatApp;

ChatServer::ChatServer(std::string ip) {
  this->ip = ip;
}

ChatServer::~ChatServer() {

}

std::string ChatServer::wait_and_get_message(void) {
  std::this_thread::sleep_for((std::chrono::milliseconds) 2000);
  srand(time(NULL));

  std::string message = "Here is a random number: " + std::to_string(rand() % 100);

  return message;
}