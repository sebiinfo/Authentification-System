#include <iostream>
#include "password.hpp"
#include <string>
#include <vector>
#include <ctime>

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char random_character(){
    // Random string generator function.
    return alphanum[rand() % stringLength];
}

Profile::Profile(){
    // Initializes everything
    random=0;
    salt="";
    hashed="";
    user="";
}

std::vector<std::string> Profile::build_profile(std::string entered_username, std::string password_1, std::string confirm_password){
    std::vector<std::string> vect;
    if (password_1 == confirm_password){
        user = entered_username;
        vect.push_back(user);
        std::string hashed_password = encrypt(password_1);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

bool Profile::compare_password(std::string entered_username, std::string password_entered, std::string password_from_database){
    // Check user first and use salt from user
    std::string hashed_password = encrypt(password_entered);
    if (hashed_password == password_from_database) {
        return true;
    }
    return false;
}

std::vector<std::string> Profile::change_password(std::string username, std::string old_password, std::string new_password, std::string confirm_new_password){
    std::vector<std::string> vect;
    //Check if user and old password match in database
    if (new_password == confirm_new_password){
        user = username;
        vect.push_back(user);
        std::string hashed_password = encrypt(new_password);
        hashed = hashed_password;
        vect.push_back(hashed);
    }
    return vect;
}

std::string Profile::encrypt(std::string password){
    if (salt.empty()){
        generate_salt();
    }
    std::string longer_password_to_encrypt = password+salt;
    std::string h = hash_it(longer_password_to_encrypt);
    for (int i=0;i<10;i++){
        h=hash_it(h);
    }
    return h;
}

std::string Profile::hash_it(std::string CandidatePass){
    int length_CandidatePass = CandidatePass.length();
    long long hp = 0;

    srand(time(0));
    if (random == 0) {
        random = rand() % (Q - 1) + 1; // generating random value x
    }
    for(int i=0; i< length_CandidatePass ;i++) {
        hp = (random * hp) % Q; // calculating hash of Password
        hp += CandidatePass[i];
        hp %= Q;
    }
    std::string h = std::to_string(hp);
    return h;
};

void Profile::generate_salt(){
    for (int i = 0; i < 32; i++) {
        salt += generate_random();
    }
}

void Profile::set_random(long long r) {
    random = r;
}
void Profile::set_salt(std::string s) {
    salt = s;
}
std::string Profile::generate_random(){
    // generate a random string of length 12
    std::string random_string;
    for(int i=0; i <= 12; i++) {
        random_string.push_back(random_character());
    }
    return random_string;
}

// Class Password

// Password::Password() {
//     // Create a random password
//     generate_salt();
//     cout << "Creating a password ..." << endl;
//     password = generate_random();
//     cout << "Your new password is: " << password << endl;
//     encrypt();
//     change_password();
// }

// Password::Password(string pwd) {
//     password = pwd;
//     encrypt();
// }


// Password::~Password() {
//     password.clear();
//     hashed.clear();
// }

// bool Password::operator==(Password &other) {
//     other.encrypt();
//     return get_hash() == other.get_hash();
// }

// string Password::generate_random() {
//     string s;
//     for(int i=0; i <= 12; i++) {
//         s.push_back(random_character());
//     }
//     return s;
// }

// void Password::generate_salt() {
//     for (int i = 0; i < 32; i++) {
//         salt += generate_random();
//         // MAKE SURE SALT IS UNIQUE
//     }
// }
// string Password::hash_it(string CandidatePass){
//         int l1 = CandidatePass.length();
//         long long hp = 0;

//         srand(time(0));
//         if (random==0) {
//             random = rand() % (Q - 1) + 1; // generating random value x
//         }
//         for(int i=0; i<l1 ;i++) {
//             hp = (random * hp) % Q; // calculating hash of Password
//             hp += CandidatePass[i];
//             hp %= Q;
//         }
//             string h=to_string(hp);

//         return h;
//         };

// void Password::encrypt() {
//     if (! salt.empty()){
//             string candidatePass= password+salt;
//             string h;
//             for (int i=0;i<10;i++){
//                 h = hash_it(candidatePass);
//             }
//             hashed=h;
//     }
// }


// void Password::change_password() {
//     cout << "Would you like to change your password ? (Y/N)" << endl;
//     string answer;
//     cin >> answer;
//     if (answer == "Y"){
//         cout << "Choose a new password: " << endl;
//         string pwd;
//         cin >> pwd;
//         cout << "Confirm your password: " << endl;
//         string pwd2;
//         cin >> pwd2;
//         if (pwd == pwd2) {
//             password = pwd;
//             encrypt();
//         }
//         cout << "Password changed !" << endl;
//     } else {
//         cout << "The password won't be changed" << endl;
//     }
// }

// // Class Username

// Username::Username() {
//     string confirm="0";
//     while (confirm!="Y") {
//         string input;
//         cout << "Create your username:";
//         cin >> input;
//         cout << "Your username is: ";
//         cout << input << endl;
//         cout << "Do you confirm? (Y/N)";
//         cin >> confirm;
//         if (confirm == "Y") {
//             user = input;
//             break;
//         } else if (confirm == "N") {
//             continue;
//         }
//         else {
//             while (confirm != "Y" && confirm != "N") {
//                 cout << "Do you confirm? (Y/N)";
//             }
//         }
//     }
// }
// bool Username:: operator == (Username &other){
//     return get_user()==other.get_user();
// }

// void Username::change_username(){
//     cout << "Would you like to change your username ? (Y/N)" << endl;
//     string answer;
//     cin >> answer;
//     if (answer == "Y"){
//         cout << "Choose a new username: " << endl;
//         string us;
//         cin >> us;
//         cout << "Confirm your username: " << endl;
//         string us2;
//         cin >> us2;
//         if (us == us2) {
//             user = us;
//         }
//         cout << "Username changed !" << endl;
//     } else {
//         cout << "The username won't be changed" << endl;
//     }
// }

// // Class Profile

// Profile::Profile(){
//     // Create a profile
//     user=Username();
//     pwd=Password();
// }

// bool Profile:: operator==(Profile &other){
//     return (get_username() == other.get_username() && get_password_hash()== other.get_password_hash());
// }
