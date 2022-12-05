#include <iostream>
#include <string>
#include <vector>
#include "password.hpp"
// #include "password.cpp"
#include "tests.cpp"

using namespace std;

int main() {
    bool test = false;
    if (test) { // Test doesn't work (it crashes directly) why ?
        cout << "Starting test ..." << endl;
        tests();
        cout << "Test finished !" << endl;
        cout << "Results of the test are in the file results_test.txt" << endl;
    } else {
        string user;
        cout << "Enter username: "<<endl;
        cin >> user;
        string pwd;
        cout << "Enter password: "<<endl;
        cin >> pwd;
        string pwd2;
        cout << "Confirm password: "<<endl;
        cin >> pwd2;
        Profile p;
        std::vector<string> v = p.build_profile(user,pwd, pwd2);
        cout<<"Username: "<< p.get_username() <<endl;
        cout<<"Salt is: "<< p.get_salt() << endl;
        cout<<"Random string used for hash: "<< p.get_random() << endl;
        cout<<"Hashed password: "<< p.get_hash() << endl;
    }
    return 0;

}
