#include <iostream>
#include "password.hpp"
#include <string>
#include <clib>
#include <ctime>
using namespace std;

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char random_character()  // Random string generator function.
{
    return alphanum[rand() % stringLength];
}

// Class Password

// Create a random password
Password::Password() {
    cout << "Creating a password ..." << endl;
    password = generate_random();
    cout << "Your new password is: " << password << endl;
    encrypt();
}

Password::Password(string pwd) {
    password = pwd;
    encrypt();
}

Password~Password() {}

bool Password::operator==(Password &other) {
    other.encrypt();
    return get_hash() == other.get_hash();
}

string Password::generate_random() {
    string s;
    for(int i=0; i <= 12; i++) {
        s.push_back(random_character());
    }
    return s;
}

string Password::generate_salt(){
    return 32*genRandom();
    // MAKE SURE SALT IS UNIQUE
}


string Password::encrypt() {
    str s= generate_salt();
    hash <string> hash;
    string candidatePass= password+s;
    string h;
    for (int i=0;i<10;i++){
        h=hash(candidatePass);
    }
    return h;
}


void Password::change_password() {
    cout << "Are you sure you want to change your password ? (Y/N)" << endl;
    char answer;
    cin >> answer;
    if (answer == *"Y"){
        cout << "Choose a new password: " << endl;
        string pwd;
        cin >> pwd;
        cout << "Confirm your password: " << endl;
        string pwd2;
        cin >> pwd2;
        if (pwd == pwd2) {
            password = pwd;
            encrypt();
        }
        cout << "Password changed !" << endl;
    } else {
        cout << "Exiting ..." << endl;
        exit(0);
    }
}

//void Password::show_password() {
//    cout << "Your password is:" << endl;
//    cout << password << endl;
//}

void Password::reset() {
    password.clear();
    hashed.clear();
}

bool Password::compare_password(){
    string username;
    cout<<"Enter Username";
    cin>>username;
    string enteredpass;
    cout<<"Enter Password";
    cin>>enteredpass;
    Password pass = Password(enteredpass);
    string nenteredpass= pass.encrypt();
}


