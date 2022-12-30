#ifndef TESTS_HPP
#define TESTS_HPP
#include "password.hpp"
#include <iostream>
#include <string>
#include <vector>

class TestPassword {
  public:
    static void tests();
    static void compare(std::vector<std::string> list_hash,
                        std::vector<std::string> list_words);
};

#endif // TESTS_HPP
