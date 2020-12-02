#include <iostream>
#include "card.h"

using namespace MiniGame;

std::string string_value(int value) {
  if (value == 1) return "A";
  if (value < 11) return std::to_string(value);
  if (value == 11) return "J";
  if (value == 12) return "D";
  return "K";
}

Card::Card(Card::type type, int value) {
  Card::_type = type;
  Card::_value = value;

  Card::_value_top = string_value(value).append(value != 10 ? " " : "");
  Card::_value_bottom = (std::string (value != 10 ? " " : "")).append(string_value(value));
}

Card::Card() {
  srand(time(NULL));

  int value = rand() % 13 + 1;

  this->_type = Card::type(rand() % 4);
  Card::_value = value;

  Card::_value_top = string_value(value).append(value != 10 ? " " : "");
  Card::_value_bottom = (std::string (value != 10 ? " " : "")).append(string_value(value));
}

std::string Card::to_string(void) const {
  std::string lines[9] = {
    "┌─────────┐",
    "│         │",
    "│         │",
    "│         │",
    "│         │",
    "│         │",
    "│         │",
    "│         │",
    "└─────────┘"
  };

  std::string color = (Card::_type == Card::hearts || Card::_type == Card::diamonds) ? "\033[1;31m" : "\033[1;30m";

  lines[1] = ((std::string) "│         │").replace(3, 2, color + Card::_value_top + "\033[0m");
  lines[7] = ((std::string) "│         │").replace(10, 2, color + Card::_value_bottom + "\033[0m");

  if (Card::_type == Card::hearts) lines[4]   = "│    \033[1;31m♥\033[0m    │";
  if (Card::_type == Card::diamonds) lines[4] = "│    \033[1;31m♦\033[0m    │";
  if (Card::_type == Card::spades) lines[4]   = "│    \033[1;30m♠\033[0m    │";
  if (Card::_type == Card::clubs) lines[4]    = "│    \033[1;30m♣\033[0m    │";

  std::string s = "";
  for(int i = 0; i < 9; i++) s += i == 0 ? lines[i] : "\n" + lines[i];
  return s;
}

int Card::get_value() const {
  return Card::_value;
}