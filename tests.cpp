#include <iostream>
#include "tests.h"
#include "password.cpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void tests(){
    std::vector< std::string > list;
    std::fstream file;
    file.open("words.txt",std::ios::in); //open a file to perform read operation using file object
       if (file.is_open()){   //checking whether the file is open
          std::string tp;
          while(getline(file, tp)){ //read data from file object and put it into string.
             list.push_back(tp); //print the data of the string
          }
       }
    file.close();
    std::vector<std::string> list_hash;
    for(int i=0; i < sizeof(list); i++){
        Password p(list[i]);
        p.encrypt();
        list_hash.push_back(p.get_hash());
    }
    compare(list_hash, list);
}

void compare(std::vector<std::string> list_hash, std::vector<std::string> list){
    std::fstream outfile;
    outfile.open("results_test.txt",std::ios::out);
    for(int i = 0; i< sizeof(list_hash); i++){
        for(int j= i+1; j < sizeof(list_hash); j++){
            if (list_hash[i] == list_hash[j]){
                outfile << "Same hash ("<< list_hash[i] << ") for words : " << list[i] << " and " << list[j] << std::endl;
            }
        }
    }
    outfile.close();
}

int main(){
    cout << "Starting test ..." << endl;
    tests();
    cout << "Test finished !" << endl;
    cout << "Results of the test are in the file results_test.txt" << endl;
    return 0;
}
