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

ChatApp::User * User::get_user(WebSocket::Connection * connection) {
  for (int i = 0; i < users.size(); i++) if (users[i].get_connection() == connection) return &users[i];
  throw "user_not_found";
}

ChatApp::User * User::get_user(std::string username) {
  for (int i = 0; i < users.size(); i++) if (users[i].get_username() == username) return &users[i];
  throw "user_not_found";
}

void User::add_user(ChatApp::User user) {
  users.push_back(user);
}

void User::delete_user(WebSocket::Connection * connection) {
  for (int i = 0; i < users.size(); i++) if (users[i].get_connection() == connection) users.erase(users.begin() + i);
}