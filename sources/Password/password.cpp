#include "password.hpp"
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>

static const char alphanum[] = "0123456789"
                               "!@#$%^&*():;<>?"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char random_character() {
    // Random string generator function.
    return alphanum[rand() % stringLength];
}

bool Profile::validate_password(std::string password) {
    if (password.length() < 9) {
        return false;
    }
    std::set<char> special_characters = {'!', '@', '#', '$', '%', '^', '&', '*',
                                         '(', ')', ';', ':', '<', '>', '?'};
    std::set<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::set<char> capital_letters = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    std::set<char> small_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int nbr_special_characters = 0, nbr_capital_letters = 0,
        nbr_small_letters = 0, nbr_numbers = 0;
    for (int i = 0; i < password.length(); i++) {
        if (numbers.count(password[i]) > 0) {
            nbr_numbers++;
        } else if (special_characters.count(password[i]) > 0) {
            nbr_special_characters++;
        } else if (capital_letters.count(password[i]) > 0) {
            nbr_capital_letters++;
        } else {
            nbr_small_letters++;
        }
    }
    if ((nbr_numbers == 0) || (nbr_special_characters == 0) ||
        (nbr_capital_letters == 0) || (nbr_small_letters == 0)) {
        return false;
    }
    return true;
}

Profile::Profile() {
    // Initializes everything
    random = 0;
    Q = pow(2,82589933) − 1;
    salt = "";
    hashed = "";
    user = "";
}

std::vector<std::string> Profile::build_profile(std::string username_entered,
                                                std::string password_1,
                                                std::string confirm_password) {
    std::vector<std::string> vect;
    if ((validate_password(password_1)) && (password_1 == confirm_password)) {
        user = username_entered;
        vect.push_back(user);
        std::string hashed_password = encrypt(password_1);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

bool Profile::compare_password(std::string username_entered,
                               std::string password_entered,
                               std::string password_from_database,
                               std::string salt_from_database) {
    // Check user first
    set_salt(salt_from_database);
    std::string hashed_password = encrypt(password_entered);
    if (hashed_password == password_from_database) {
        return true;
    }
    return false;
}

std::vector<std::string>
Profile::change_password(std::string username, std::string old_password,
                         std::string new_password,
                         std::string confirm_new_password) {
    std::vector<std::string> vect;
    // Check if user and old password match in database
    if ((validate_password(new_password)) &&
        (new_password == confirm_new_password)) {
        user = username;
        vect.push_back(user);
        std::string hashed_password = encrypt(new_password);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

std::string Profile::encrypt(std::string password) {
    if (salt.empty()) {
        generate_salt();
    }
    std::string longer_password_to_encrypt = password + salt;
    std::string h = hash_it(longer_password_to_encrypt);
    for (int i = 0; i < 10; i++) {
        h = hash_it(h);
    }
    return h;
}

std::string Profile::hash_it(std::string CandidatePass) {
    int length_CandidatePass = CandidatePass.length();
    long long hp = 0;

    srand(time(0));
    if (random == 0) {
        random = rand() % (Q - 1) + 1; // generating random value x
    }
    for (int i = 0; i < length_CandidatePass; i++) {
        hp = (random * hp) % Q; // calculating hash of Password
        hp += CandidatePass[i];
        hp %= Q;
    }
    std::string h = std::to_string(hp);
    return h;
};

void Profile::generate_salt() { salt = generate_random(32); }

void Profile::set_random(long long r) { random = r; }
void Profile::set_salt(std::string s) { salt = s; }
std::string Profile::generate_random(int length) {
    // generate a random string of size length
    std::string random_string;
    for (int i = 0; i < length; i++) {
        random_string.push_back(random_character());
    }
    return random_string;
}
