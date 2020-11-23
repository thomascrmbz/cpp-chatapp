#include "chat_server.h"

#include <thread>
#include <chrono>

using namespace ChatApp;

ChatServer::ChatServer(std::string ip, ChatApp::ChatUI * chatUI) {
  this->ip = ip;
  this->chatUI = chatUI;

  std::thread(&ChatServer::listen, this).detach();

}

ChatServer::~ChatServer() {

}

void ChatServer::listen(void) {
  WebSocket::Client client(this->ip);

  client.on_connection = [&](WebSocket::Connection * connection) {

    this->ws_connection = connection;

    connection->on_message = [&](std::string message) {
      this->chatUI->output(message);
    };
  };

  client.connect();
}

void ChatServer::send(std::string message) {
  this->ws_connection->write(message);
}