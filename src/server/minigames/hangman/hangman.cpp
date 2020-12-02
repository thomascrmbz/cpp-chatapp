#include "hangman.h"

#include <iostream>
#include <chrono>
#include <thread>

#include "hangman_art.h"

using namespace MiniGame;

Hangman::Hangman(std::vector<ChatApp::User> * users) {
  this->users = users;
}

void Hangman::game_loop(void) {
  while (true) {
    for (int i = 0; i < this->users->size(); i++) {
      WebSocket::Frame frame(hangman_workbench[5] + "\n_ _ _ _ _ _\nguess with !x");
      frame.set_opcode(0xB);
      this->users->at(i).get_connection()->write(frame);
    }
    
    std::this_thread::sleep_for((std::chrono::milliseconds) 1000);
  }
  
}