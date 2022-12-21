#include "password.hpp"
#include "tests.cpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    bool test_hashing =
        true; // Put to true if you want to test the hashing function

    if (test_hashing) {
        std::cout << "Starting test ..." << std::endl;
        Test t;
        t.tests();
        std::cout << "Test finished !" << std::endl;
        std::cout << "Results of the test are in the file results_test0.txt"
                  << std::endl;
    } else {
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
        std::cout << "Random string used for hash: " << p.get_random()
                  << std::endl;
        std::cout << "Hashed password: " << p.get_hash() << std::endl;
    }
    return 0;
}
