#include "password.hpp"
#include <ctime>
#include <iostream>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>

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
    salt = "";
    hashed = "";
    user = "";
}

std::vector<std::string> Profile::build_profile(std::string username_entered,
                                                std::string password_1,
                                                std::string confirm_password) {
    std::vector<std::string> vect;
    if(! d.check_username("new.csv", username_entered)) {
        std::cout << "Username already taken" << std::endl;
        return vect;
    }
    if ((validate_password(password_1)) && (password_1 == confirm_password)) {
        user = username_entered;
        vect.push_back(user);
        std::string hashed_password = encrypt(password_1);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    bool v = d.writeDataToFile("new.csv", user, hashed, salt);
    return vect;
}

bool Profile::compare_password(std::string username_entered,
                               std::string password_entered) {
    std::vector<std::string> line_in_file = d.readRecordFromFile("new.csv", username_entered);
    if(line_in_file.empty()) {
        std::cout << "No matching username" << std::endl ;
        return false;
    }
    std::string password_from_database = line_in_file[2];
    std::string salt_from_database = line_in_file[3];
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
    if(d.checkPasswordandUsername("new.csv", username, old_password)){
        if ((validate_password(new_password)) &&
            (new_password == confirm_new_password)) {
            user = username;
            vect.push_back(user);
            std::string hashed_password = encrypt(new_password);
            hashed = hashed_password;
            vect.push_back(hashed);
        }
    }
    return vect;
}

std::string Profile::encrypt(std::string password) {
    if (salt.empty()) {
        generate_salt();
    }
    std::string longer_password_to_encrypt = password + salt;
    std::string h = hash_it(longer_password_to_encrypt);
    for (int i = 0; i <10; i++) {
        h = hash_it(h);
    }
    return h;
}

void Profile::generate_salt() { salt = generate_random(10); }

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

std::string Profile::hash_it(const std::string& CandidatePass) {
        const uint32_t m = 0x5bd1e995;
        const int r = 24;
        const int iterations = 1000;  // Number of iterations

        uint64_t h = 0;

        // Get the length of the input string
        int len = CandidatePass.length();

        // Mix 4 bytes at a time into the hash
        const unsigned char *data = reinterpret_cast<const unsigned char *>(CandidatePass.data());
        while (len >= 4) {
            uint32_t k = *(uint32_t *)data;

            k *= m;
            k ^= k >> r;
            k *= m;

            h *= m;
            h ^= k;

            data += 4;
            len -= 4;
        }

        // Handle the last few bytes of the input array
        switch (len) {
            case 3:
                h ^= data[2] << 16;
            case 2:
                h ^= data[1] << 8;
            case 1:
                h ^= data[0];
                h *= m;
        }

        // Do a large number of final mixes of the hash to ensure the last few
        // bytes are well-incorporated.
        for (int i = 0; i < iterations; i++) {
            h ^= h >> 13;
            h *= m;
            h ^= h >> 15;
        }

        std::string result;
        result.resize(8);
        memcpy(&result[0], &h, 8);
        return result;
    }


