#pragma once

namespace MiniGame {

  class Card {

    public:
      enum type {
        hearts,
        diamonds,
        spades,
        clubs
      };
      Card(Card::type type, int value);
      Card();
      void print() const;
      int get_value() const;
      std::string to_string(void) const;

    private:
      Card::type  _type;
      int         _value;
      std::string _value_top;
      std::string _value_bottom;
  };

}