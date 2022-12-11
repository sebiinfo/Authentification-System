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
    std::vector<std::string> build_profile(std::string user, std::string pwd1, std::string pwd2);
    bool compare_password(std::string user, std::string pwd1, std::string pwd2);
    std::vector<std::string> change_password(std::string user, std::string old, std::string new1, std::string new2);

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
