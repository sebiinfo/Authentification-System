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

    std::string generate_random();
    void encrypt();
    void change_password();
    std::string get_hash() {return hashed;};
    //void show_password();
    void reset();

private:
    std::string password;
    std::string hashed;
};


#endif // PASSWORD_HPP
