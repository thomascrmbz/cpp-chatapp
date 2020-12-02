#include "chat_server.h"

#include <thread>
#include <chrono>

using namespace ChatApp;

ChatServer::ChatServer(std::string ip, ChatApp::ChatUI * chatUI, std::string username) {
  this->ip = ip;
  this->chatUI = chatUI;
  this->username = username;

  std::thread(&ChatServer::listen, this).detach();

}

ChatServer::~ChatServer() {

}

void ChatServer::listen(void) {
  WebSocket::Client client(this->ip);

  client.on_connection = [&](WebSocket::Connection * connection) {

    this->ws_connection = connection;

    WebSocket::Frame frame(this->username);
    frame.set_opcode(0x3);
    connection->write(frame);

    connection->on_message = [&](WebSocket::Frame frame) {
      std::string payload = frame.get_payload();
      std::string username = payload.substr(payload.find_first_of("!") + 1, payload.find_first_of(";") - payload.find_first_of("!") - 1);
      std::string message = payload.substr(payload.find_first_of(";") + 1, payload.size() - 1);

      if (frame.get_opcode() == 0x01) this->chatUI->output(username, message);
      if (frame.get_opcode() == 0x04) this->chatUI->output("\e[1;35mFrom \e[0m" + username, message);
      if (frame.get_opcode() == 0xB) this->chatUI->output(payload);
    };
  };

  client.connect();
}

void ChatServer::send(std::string message) {
  if (message.find("private!") == 0) {
    WebSocket::Frame frame(message.substr(message.find("!") + 1, message.size() - 1));
    frame.set_opcode(0x04);
    this->ws_connection->write(frame);
  }
  else if (message == "minigame!hangman;start" || message == "minigame!card;start") {
    WebSocket::Frame frame(message);
    frame.set_opcode(0xB);
    this->ws_connection->write(frame);
  }
  else this->ws_connection->write(message);
}