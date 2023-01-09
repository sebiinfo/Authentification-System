#include "password.hpp"
#include "tests.cpp"
#include "tests.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::string user;
    std::cout << "Enter username: " << std::endl;
    std::cin >> user;
    std::string pwd;
    std::cout << "Enter password: " << std::endl;
    std::cin >> pwd;
    std::string pwd2;
    std::cout << "Confirm password: " << std::endl;
    std::cin >> pwd2;
    Profile p = Profile();

    std::vector<std::string> v = p.build_profile(user, pwd, pwd2);
    std::cout << "Username: " << p.get_username() << std::endl;
    std::cout << "Salt is: " << p.get_salt() << std::endl;
    std::cout << "Random string used for hash: " << p.get_random() << std::endl;
    std::cout << "Hashed password: " << p.get_hash() << std::endl;
    return 0;
}
