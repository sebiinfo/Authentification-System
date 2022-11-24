#include <iostream>
#include "password.hpp"

char random_character(){
    return 'a' + rand()%26;
}

Password::Password() {
    std::cout << "Creating a password ..." << std::endl;
    password = generate_random();
    std::cout << "Your new password is: " << password << std::endl;
    encrypt();
}

Password::Password(std::string pwd) {
    password = pwd;
    encrypt();
}

Password::~Password() {}

bool Password::operator==(Password &other) {
    other.encrypt();
    return get_hash() == other.get_hash();
}

std::string Password::generate_random() {
    std::string s;
    for(int i=0; i <= 12; i++) {
        s.push_back(random_character());
    }
    return s;
}

void Password::encrypt() {}

void Password::change_password() {
    std::cout << "Are you sure you want to change your password ? (Y/N)" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer == *"Y"){
        std::cout << "Choose a new password: " << std::endl;
        std::string pwd;
        std::cin >> pwd;
        std::cout << "Confirm your password: " << std::endl;
        std::string pwd2;
        std::cin >> pwd2;
        if (pwd == pwd2) {
            password = pwd;
            encrypt();
        }
        std::cout << "Password changed !" << std::endl;
    } else {
        std::cout << "Exiting ..." << std::endl;
        exit(0);
    }
}

//void Password::show_password() {
//    std::cout << "Your password is:" << std::endl;
//    std::cout << password << std::endl;
//}

void Password::reset() {
    password.clear();
    hashed.clear();
}

