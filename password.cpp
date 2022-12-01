#include <iostream>
#include "password.hpp"
#include <string>
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
    generate_salt();
    cout << "Creating a password ..." << endl;
    password = generate_random();
    cout << "Your new password is: " << password << endl;
    encrypt();
    change_password();
}


Password::~Password() {
    password.clear();
    hashed.clear();
}

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

void Password::generate_salt() {
    for (int i = 0; i < 32; i++) {
        salt += generate_random();
        // MAKE SURE SALT IS UNIQUE
    }
}
string Password::get_salt() {return salt;};

void Password::encrypt() {
    if (!salt.empty()){
            string candidatePass= password+salt;
            string h;
            for (int i=0;i<10;i++){
                h = str_hash(candidatePass);
            }
            hashed=h;
    }
}


void Password::change_password() {
    cout << "Would you like to change your password ? (Y/N)" << endl;
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

string Password:: get_hash(){
    return hashed;
}

// Class Username

Username::Username() {
    string confirm="0";
    while (confirm!="Y") {
        string input;
        cout << "Create your username:";
        cin >> input;
        cout << "Your username is: ";
        cout << input << endl;
        cout << "Do you confirm? (Y/N)";
        if (confirm == "Y") {
            user = input;
            break;
        } else if (confirm == "N") {
            continue;
        }
        else {
            while (confirm != "Y" && confirm != "N") {
                cout << "Do you confirm? (Y/N)";
            }
        }
    }
}
bool Username:: operator == (Username &other){
    return get_user()==other.get_user();
}
string Username::get_user(){
    return user;
}


// Class Profile

Profile::Profile(){
    user=Username();
    pwd=Password();
}
string Profile::get_username() {
    return user.get_user();
}
string Profile::get_password_hash() {
    return pwd.get_hash();
}
bool Profile:: operator==(Profile &other){
    return (get_username() == other.get_username() && get_password_hash()== other.get_password_hash());
}

bool Profile::success(Profile p){
    return (user==p.user && pwd==p.pwd);
}


