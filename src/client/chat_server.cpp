#include "chat_server.h"

#include <future>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace ChatApp;

ChatServer::ChatServer(std::string ip) {
  this->ip = ip;
}

ChatServer::~ChatServer() {

}

std::string ChatServer::wait_and_get_message(void) {
  std::this_thread::sleep_for((std::chrono::milliseconds) 2000);
  printf("\033[1A");

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%H:%M:%S");
  auto str = oss.str();

  return "\n" + str + "    fake_user \033[1;31m|\033[0m new message\n> ";
}