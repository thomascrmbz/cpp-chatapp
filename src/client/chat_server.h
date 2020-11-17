#pragma once

#include <string>

namespace ChatApp {

  class ChatServer {

    public:
      ChatServer(std::string ip);
      ~ChatServer();    

    private:
      std::string ip;
  };
}