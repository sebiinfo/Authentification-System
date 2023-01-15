#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <iostream>
#include <string>
#include <vector>

char random_character();

class Profile {
  public:
    Profile();
    std::vector<std::string> build_profile(std::string username_entered,
                                           std::string password_1,
                                           std::string confirm_password);
    bool compare_password(std::string username_entered,
                          std::string password_entered,
                          std::string password_from_database,
                          std::string salt_from_database);
    std::vector<std::string> change_password(std::string username,
                                             std::string new_password,
                                             std::string confirm_new_password);
    bool validate_password(std::string password);

    std::string encrypt(std::string password);
    std::string hash_it(const std::string& CandidatePass);

    void generate_salt();
    std::string generate_random(int length);

    void set_random(long long r);
    void set_salt(std::string s);

    std::string get_hash() { return hashed; }
    std::string get_salt() { return salt; }
    long long get_random() { return random; }
    std::string get_username() { return user; }

  private:
    std::string user;
    std::string hashed;
    std::string salt;
    long long random;
};

#endif // PASSWORD_HPP
