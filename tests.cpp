#include <iostream>
#include "tests.hpp"
#include "password.cpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Test::tests(){
    vector<string> list;
    ifstream f("/Users/jwatissee/Desktop/Authentification-System/cmake-build-debug/words_for_testing.txt"); //open a file to perform read operation using file object
    if (f.is_open()){   //checking whether the file is open
        string line;
        while(getline(f, line)){ //read data from file object and put it into string.
            list.push_back(line); //print the data of the string
        }
    } else {
        cerr << "Error " << strerror(errno);
    }
    f.close();
    vector<string> list_hash;
    for(int i=0; i < sizeof(list); i++){
        Profile p;
        string h = p.encrypt(list[i]);
        list_hash.push_back(h);
    }
    compare(list_hash, list);
}

void Test::compare(vector<string> list_hash, vector<string> list){
    ofstream outfile("/Users/jwatissee/Desktop/Authentification-System/cmake-build-debug/results_test.txt");
    for(int i = 0; i< sizeof(list_hash); i++){
        outfile << i << endl;
        for(int j= i+1; j < sizeof(list_hash); j++){
            if (list_hash[i] == list_hash[j]){
                outfile << "Same hash ("<< list_hash[i] << ") for words : " << list[i] << " and " << list[j] << endl;
            }
        }
    }
    outfile.close();
}
