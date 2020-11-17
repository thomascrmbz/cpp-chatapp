#pragma once

#include <string>

namespace ChatApp {

  class ChatServer {

    public:
      ChatServer(std::string ip);
      ~ChatServer();

    public:
      std::string wait_and_get_message(void);

    private:
      std::string ip;
  };
}