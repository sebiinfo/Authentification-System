#include "tests.hpp"
#include "password.cpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void TestPassword::tests() {
    std::cout << "Starting test ..." << std::endl;
    // Function to test the hashes
    std::vector<std::string> list_of_words;
    /* std::ifstream infile(
        "/Users/jwatissee/Desktop/cmake-build-debug/words_for_testing.txt"); */
    std::ifstream infile("./words_for_testing.txt");
    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            list_of_words.push_back(line);
        }
    } else {
        std::cerr << "Error " << std::strerror(errno);
    }
    infile.close();
    std::vector<std::string> list_of_hash;
    for (int i = 0; i < list_of_words.size(); i++) {
        Profile profile;
        std::string hash = profile.encrypt(list_of_words[i]);
        list_of_hash.push_back(hash);
    }
    compare(list_of_hash, list_of_words);
    std::cout << "Test finished !" << std::endl;
    std::cout << "Results of the test are in the file results_test0.txt"
              << std::endl;
}

void TestPassword::compare(std::vector<std::string> list_hash,
                           std::vector<std::string> list_words) {
    // Function to compare the hashes
    /* std::ofstream outfile(
        "/Users/jwatissee/Desktop/cmake-build-debug/results_test.txt"); */
    std::ofstream outfile("./results_test0.txt");
    std::vector<std::pair<std::string, std::string>> hash_and_pwd;
    for (int i = 0; i < list_hash.size(); i++) {
        hash_and_pwd.push_back(std::make_pair(list_hash[i], list_words[i]));
    }
    std::sort(hash_and_pwd.begin(), hash_and_pwd.end());
    for (int i = 0; i < list_hash.size() - 1; i++) {
        // outfile << list_hash[i] << std::endl;
        if (hash_and_pwd[i].first == hash_and_pwd[i + 1].first) {
            outfile << "Same hash: " << hash_and_pwd[i].second << " and "
                    << hash_and_pwd[i + 1].second << "found !" << std::endl;
        }
    }
    outfile.close();
}
