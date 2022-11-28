#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>

char random_character();


class Password {
public:
    Password();
    Password(std::string pwd);
    ~Password();

    bool operator==(Password &other);

    std::string generate_random_password();
    std::string generate_salt();
    std::string encrypt();
    if username.salt==NULL:
       salt=generatesalt
     else:
    void change_password();
    bool compare_password();
    std::string get_hash() {return hashed;};
    //void show_password();
    void reset();

private:
    std::string password;
    std::string hashed;
    std::string salt;
};


#endif // PASSWORD_HPP
