#include "user.h"

using namespace ChatApp;

User::User(std::string username, WebSocket::Connection * connection) {
  this->username = username;
  this->connection = connection;
}

std::string User::get_username(void) {
  return this->username;
}

WebSocket::Connection * User::get_connection(void) {
  return this->connection;
}