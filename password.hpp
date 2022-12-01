#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
using namespace std;

char random_character();


class Password {
public:
    Password();
    Password(std::string pwd);
    ~Password();

    bool operator==(Password &other);

    string generate_random_password();
    string generate_salt();
    string encrypt();
    void change_password();
    bool compare_password();
    string get_hash() {return hashed;};
    //void show_password();
    void reset();

private:
    string password;
    string hashed;
    string salt;
};

class Username{
public:
    Username();
    Username(string input);
    change_username(string input);
private:
    string user;
};

class Profile{
public:
    Profile();
    Profile(string U, string p);
private:
    Username user;
    Password pwd;
};

#endif // PASSWORD_HPP
