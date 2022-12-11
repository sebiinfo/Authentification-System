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
    random=0;
    salt="";
    hashed="";
    user="";
}

std::vector<std::string> Profile::build_profile(std::string user, std::string pwd1, std::string pwd2){
    std::vector<std::string> vect;
    if (pwd1 == pwd2){
        user = user;
        vect.push_back(user);
        std::string h = encrypt(pwd1);
        hashed = h;
        vect.push_back(hashed);
    }
    return vect;
}

bool Profile::compare_password(std::string user, std::string pwd1, std::string pwd2){
    //pwd1 is the string entered by the user
    // pwd2 is the hashed password in the database associated to user

    // Check user first and use salt from user
    std::string h = encrypt(pwd1);
    if (pwd1 == pwd2) {
        return true;
    }
    return false;
}

std::vector<std::string> Profile::change_password(std::string user, std::string old, std::string new1, std::string new2){
    std::vector<std::string> vect;
    //Check if user and old password match in database
    if (new1 == new2){
        user = user;
        vect.push_back(user);
        std::string h = encrypt(new1);
        hashed = h;
        vect.push_back(hashed);
    }
    return vect;
}

std::string Profile::encrypt(std::string password){
    if (salt.empty()){
        generate_salt();
    }
    std::string candidatePass= password+salt;
    std::string h=hash_it(candidatePass);
    for (int i=0;i<10;i++){
        h=hash_it(h);
    }
    return h;
}

std::string Profile::hash_it(std::string CandidatePass){
        int l1 = CandidatePass.length();
        long long hp = 0;

        srand(time(0));
        if (random == 0) {
            random = rand() % (Q - 1) + 1; // generating random value x
        }
        for(int i=0; i<l1 ;i++) {
            hp = (random * hp) % Q; // calculating hash of Password
            hp += CandidatePass[i];
            hp %= Q;
        }
            std::string h=std::to_string(hp);

        return h;
};

void Profile::generate_salt(){
    for (int i = 0; i < 32; i++) {
        salt += generate_random();
    }
}
void Profile::set_random(long long r) {
    random=r;
}
void Profile::set_salt(std::string s) {
    salt=s;
}
std::string Profile::generate_random(){
    std::string s;
    for(int i=0; i <= 12; i++) {
        s.push_back(random_character());
    }
    return s;
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
