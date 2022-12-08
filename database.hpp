// DATABASE HEAD
#define DATABASE_HPP

#include <iostream>
#include <string>
using namespace std;

class Database{
public:
    string hashed;
    string salt;
    long long random;
};