#pragma once

#include <string>

namespace MiniGame {
  
  const std::string hangman_workbench[] = {
    "  ╭───╮\n  │   │\n      │\n      │\n      │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[32mO\e[0m   │\n      │\n      │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[32mO\e[0m   │\n  \e[32m│\e[0m   │\n      │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[32mO\e[0m   │\n \e[32m/│\e[0m   │\n      │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[32mO\e[0m   │\n \e[32m/│\\\e[0m  │\n      │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[32mO\e[0m   │\n \e[32m/│\\\e[0m  │\n \e[32m/\e[0m    │\n      │\n──────┴──",
    "  ╭───╮\n  │   │\n  \e[31mO\e[0m   │\n \e[31m/│\\\e[0m  │\n \e[31m/ \\\e[0m  │\n      │\n──────┴──"
  };

}
