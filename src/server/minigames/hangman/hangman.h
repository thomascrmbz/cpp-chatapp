#pragma once

#include "../../user.h"

namespace MiniGame {
  class Hangman {

    public:
      Hangman(std::vector<ChatApp::User> *);

    public:
      void game_loop(void);

    private:
      std::vector<ChatApp::User> * users;
  };
}