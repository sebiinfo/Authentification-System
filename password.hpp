#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
using namespace std;
int Q = 1000000007;

char random_character();

class Profile {
public:
    std::vector<std::string> build_profile(string user, string pwd1, string pwd2);
    bool compare_password(string user, string pwd1, string pwd2);
    std::vector<string> change_password(string user, string old, string new1, string new2);

    string encrypt(string password);
    string hash_it(string CandidatePass);
    void generate_salt();
    string generate_random();
    
    string get_hash() {return hashed;}
    string get_salt() {return salt;}
    long long get_random() {return Random;}
    string get_username() {return user;}

private:
    string user;
    string hashed;
    string salt;
    long long Random;
};

// class Password {
// public:
//     Password();
//     Password(string pwd);
//     ~Password();
//     string hash_it(string CandidatePass );
//     bool operator==(Password &other);

//     void generate_salt();
//     string generate_random();

//     void encrypt();

//     void change_password();

//     string get_hash() {return hashed;}
//     string get_salt() {return salt;}

// private:
//     string password;
//     long long random;
//     string hashed;
//     string salt;
// };

// class Username{
// public:
//     Username();
//     void change_username();
//     bool operator ==(Username &other);
//     string get_user() {return user;}

// private:
//     string user;
// };

// class Profile : public Username, public Password {
// public:
//     Profile();
//     bool operator ==(Profile &other);

//     string get_username() {return user.get_user();}
//     string get_password_hash() {return pwd.get_hash();}

// private:
//     Username user;
//     Password pwd;
// };

#endif // PASSWORD_HPP
