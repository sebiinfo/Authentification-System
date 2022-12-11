#ifndef TESTS_HPP
#define TESTS_HPP
#include <iostream>
#include <string>
#include <vector>

class Test {
public:
    void tests();
    void compare(std::vector<std::string> list_hash, std::vector<std::string> list_words);
};

#endif // TESTS_HPP
