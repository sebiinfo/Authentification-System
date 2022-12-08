#include <iostream>
#include "tests.hpp"
#include "password.cpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Test::tests(){
    vector<string> list;
    ifstream f("words_for_testing.txt");
    f.open("words_for_testing.txt",ios::in); //open a file to perform read operation using file object
    cout << f.is_open() << endl;
    if (f.is_open()){   //checking whether the file is open
        string line;
        while(getline(f, line)){ //read data from file object and put it into string.
            cout << line << endl;
            list.push_back(line); //print the data of the string
        }
    } else {
        cout << "ERROR - File could not be opened" << endl;
    }
    f.close();
    vector<string> list_hash;
    for(int i=0; i < 100; i++){
        cout << i << endl;
        Profile p;
        string h = p.encrypt(list[i]);
        list_hash.push_back(h);
    }
    compare(list_hash, list);
}

void Test::compare(vector<string> list_hash, vector<string> list){
    fstream outfile;
    outfile.open("results_test.txt",ios::out);
    for(int i = 0; i< sizeof(list_hash); i++){
        for(int j= i+1; j < sizeof(list_hash); j++){
            if (list_hash[i] == list_hash[j]){
                outfile << "Same hash ("<< list_hash[i] << ") for words : " << list[i] << " and " << list[j] << endl;
            }
        }
    }
    outfile.close();
}
