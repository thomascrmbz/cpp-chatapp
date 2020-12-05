#include "chat_server.h"

#include <thread>
#include "helper.h"

using namespace ChatApp;

ChatServer::ChatServer(std::string ip) {
  this->ip = ip;
}

ChatServer::~ChatServer() {

}

void ChatServer::set_username(std::string username) {
  this->username = username;
}

void ChatServer::connect(void) {
  std::thread(&ChatServer::listen, this).detach();
}

void ChatServer::write(std::string message, int type) {
  WebSocket::Frame frame(message);
  frame.set_opcode(type);
  this->connection->write(frame);
}

void ChatServer::listen(void) {
  WebSocket::Client client(this->ip);

  client.on_connection = [&](WebSocket::Connection * connection) {
    this->connection = connection;

    WebSocket::Frame frame(this->username);
    frame.set_opcode(0x3);
    connection->write(frame);

    connection->on_message = [&](WebSocket::Frame frame) {
      std::string payload = frame.get_payload();
      std::string username = payload.substr(payload.find_first_of("!") + 1, payload.find_first_of(";") - payload.find_first_of("!") - 1);
      std::string message = payload.substr(payload.find_first_of(";") + 1, payload.size() - 1);

      this->on_message(Helper::trim_string(username), Helper::trim_string(message), frame.get_opcode());
    };
    
    this->connected = true;
  };

  client.connect();
}

bool ChatServer::is_connected(void) {
  return this->connected;
}