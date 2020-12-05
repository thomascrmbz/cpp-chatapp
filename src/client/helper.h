#pragma once

#include <string>
#include <vector>

class Helper {

  public:
    static char getch(void);
    static std::string trim_string(std::string str);
    static std::vector<std::string> string_to_vector(std::string str);

};