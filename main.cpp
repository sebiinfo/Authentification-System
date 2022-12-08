#include <iostream>
#include <string>
#include <vector>
#include "password.hpp"
#include <map>
// #include "password.cpp"
#include "tests.cpp"
#include "database.cpp"

using namespace std;

int main() {

    bool test = true; // Put to true if you want to test the hashing function

    if (test) { // Test doesn't work (it crashes directly) why ?
        cout << "Starting test ..." << endl;
        Test t;
        t.tests();
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
        Profile p=Profile();
        map <string, Database> database;
        if (database.count(user)==0){
            Database d;
            d.hashed=p.get_hash();
            d.salt=p.get_salt();
            d.random=p.get_random();
            database[p.get_username()]=d;
        }else{
            p.set_random(database[p.get_username()].random);
            p.set_salt(database[p.get_username()].salt);
        }
        vector<string> v = p.build_profile(user,pwd, pwd2);
        cout<<"Username: "<< p.get_username() <<endl;
        cout<<"Salt is: "<< p.get_salt() << endl;
        cout<<"Random string used for hash: "<< p.get_random() << endl;
        cout<<"Hashed password: "<< p.get_hash() << endl;
    }
    return 0;

}
