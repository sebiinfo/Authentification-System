#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
#include <vector>

int Q = 1000000007;

char random_character();

class Profile {
public:
    Profile();
    std::vector<std::string> build_profile(std::string entered_username, std::string password_1, std::string confirm_password);
    bool compare_password(std::string entered_username, std::string password_entered, std::string password_from_database);
    std::vector<std::string> change_password(std::string username, std::string old_password, std::string new_password, std::string confirm_new_password);

    std::string encrypt(std::string password);
    std::string hash_it(std::string CandidatePass);
    void generate_salt();
    std::string generate_random();
    void set_random(long long r);
    void set_salt(std::string s);
    std::string get_hash() {return hashed;}
    std::string get_salt() {return salt;}
    long long get_random() {return random;}
    std::string get_username() {return user;}

private:
    std::string user;
    std::string hashed;
    std::string salt;
    long long random;
};

#endif // PASSWORD_HPP