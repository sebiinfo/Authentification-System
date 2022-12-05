#include <iostream>
#include "password.hpp"
#include "password.cpp"

using namespace std;

int main() {
    string user;
    user=cin>>"Enter username"<<endl;
    string pwd;
    pwd=cin>>"Enter pwd"<<endl;
    Profile p=build_profile(user,pwd);
    cout<<"Username:"<<p.get_username()<<endl;
    cout<<"Salt is:"<<p.get_salt();endl;
    cout<<"Random string used for hash"<<p.get_random()<<endl;
    cout<<"Hashed pwd"<<p.get_hash()<<endl;
    return 0;

}
