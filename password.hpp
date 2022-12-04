#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
using namespace std;

char random_character();

class Password {
public:
    Password();
    Password(string pwd);
    ~Password();

    bool operator==(Password &other);

    void generate_salt();
    string generate_random();

    void encrypt();

    void change_password();

    string get_hash() {return hashed;}
    string get_salt() {return salt;}

private:
    string password;
    string hashed;
    string salt;
};

class Username{
public:
    Username();

    void change_username(string input);

    bool operator ==(Username &other);

    string get_user() {return user;}

private:
    string user;
};

class Profile{
public:
    Profile();
    Profile(string U, string p);

    bool operator ==(Profile &other);

    string get_username() {return user.get_user();}
    string get_password_hash() {return pwd.get_hash();}

private:
    Username user;
    Password pwd;
};

#endif // PASSWORD_HPP
