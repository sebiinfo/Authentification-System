#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
using namespace std;

char random_character();
hash<string>str_hash;

class Password {
public:
    Password();
    ~Password();
    bool operator==(Password &other);
    string generate_random_password();
    string get_hash();
    void generate_salt();
    string get_salt();
    string generate_random();
    void encrypt();
    void change_password();

private:
    string password;
    string hashed;
    string salt;
};

class Username{
public:
    Username();
    void change_username(string input);
    string get_user();
    bool operator ==(Username &other);
private:
    string user;
};

class Profile{
public:
    Profile();
    Profile(string U, string p);
    bool operator ==(Profile &other);
    string get_username();
    string get_password_hash();
    bool success(Profile p);
private:
    Username user;
    Password pwd;
};

#endif // PASSWORD_HPP
