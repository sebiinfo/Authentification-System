#include <iostream>
#include "tests.hpp"
#include "password.cpp"
#include <fstream>
#include <string>
#include <vector>

void Test::tests(){
    // Function to test the hashes
    std::vector<std::string> list_of_words;
    std::ifstream infile("/Users/jwatissee/Desktop/cmake-build-debug/words_for_testing.txt");
    if (infile.is_open()){
        std::string line;
        while(getline(infile, line)){
            list_of_words.push_back(line);
        }
    } else {
        std::cerr << "Error " << strerror(errno);
    }
    infile.close();
    std::vector<std::string> list_of_hash;
    for(int i=0; i < sizeof(list_of_words); i++){
        Profile profile;
        std::string hash = profile.encrypt(list_of_words[i]);
        list_of_hash.push_back(hash);
    }
    compare(list_of_hash, list_of_words);
}

void Test::compare(std::vector<std::string> list_hash, std::vector<std::string> list_words){
    // Function to compare the hashes
    std::ofstream outfile("/Users/jwatissee/Desktop/cmake-build-debug/results_test.txt");
    sort(list_hash.begin(), list_hash.end() );
    for(int i = 0; i< sizeof(list_hash); i++){
        outfile << list_hash[i] << std::endl;
        if (list_hash[i] == list_hash[i+1]) {
            outfile << "Same hash ("<< list_hash[i] << ") found !" << std::endl;
        }
    }
    outfile.close();
}
