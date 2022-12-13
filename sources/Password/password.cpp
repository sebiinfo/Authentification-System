#include <iostream>
#include "password.hpp"
#include <string>
#include <vector>
#include <ctime>

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char random_character(){
    // Random string generator function.
    return alphanum[rand() % stringLength];
}

Profile::Profile(){
    // Initializes everything
    random=0;
    salt="";
    hashed="";
    user="";
}

std::vector<std::string> Profile::build_profile(std::string entered_username, std::string password_1, std::string confirm_password){
    std::vector<std::string> vect;
    if (password_1 == confirm_password){
        user = entered_username;
        vect.push_back(user);
        std::string hashed_password = encrypt(password_1);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

bool Profile::compare_password(std::string entered_username, std::string password_entered, std::string password_from_database){
    // Check user first and use salt from user
    std::string hashed_password = encrypt(password_entered);
    if (hashed_password == password_from_database) {
        return true;
    }
    return false;
}

std::vector<std::string> Profile::change_password(std::string username, std::string old_password, std::string new_password, std::string confirm_new_password){
    std::vector<std::string> vect;
    //Check if user and old password match in database
    if (new_password == confirm_new_password){
        user = username;
        vect.push_back(user);
        std::string hashed_password = encrypt(new_password);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

std::string Profile::encrypt(std::string password){
    if (salt.empty()){
        generate_salt();
    }
    std::string longer_password_to_encrypt = password+salt;
    std::string h = hash_it(longer_password_to_encrypt);
    for (int i=0;i<10;i++){
        h=hash_it(h);
    }
    return h;
}

std::string Profile::hash_it(std::string CandidatePass){
    int length_CandidatePass = CandidatePass.length();
    long long hp = 0;

    srand(time(0));
    if (random == 0) {
        random = rand() % (Q - 1) + 1; // generating random value x
    }
    for(int i=0; i< length_CandidatePass ;i++) {
        hp = (random * hp) % Q; // calculating hash of Password
        hp += CandidatePass[i];
        hp %= Q;
    }
    std::string h = std::to_string(hp);
    return h;
};

void Profile::generate_salt(){
    for (int i = 0; i < 32; i++) {
        salt += generate_random();
    }
}

void Profile::set_random(long long r) {
    random = r;
}
void Profile::set_salt(std::string s) {
    salt = s;
}
std::string Profile::generate_random(){
    // generate a random string of length 12
    std::string random_string;
    for(int i=0; i <= 12; i++) {
        random_string.push_back(random_character());
    }
    return random_string;
}
