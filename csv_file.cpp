#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <csv.hpp>

namespace std{

int test2(){
    vector<string> data = readRecordFromFile("new.txt", "password");
    return 0;
}


//registration, adding data to csv file
//need to write automatically pushing it to git and each time the file is accessed automatically retrieving it from git
bool writeDataToFile(string file_name, string username, string name, string last_name, string password, string email){
    std::ofstream file;
    file.open(file_name, ios_base::app);
    file << username << ',' << name << ',' << last_name << ','<< email << ',' << password<< endl;
    file.close();

    return true;
}

//looking for a username in a csv file and returning all data about it
vector<string> readRecordFromFile(string file_name, string username_search){
    vector<string> record;
    ifstream file;
    file.open(file_name);

    bool found = false;
    string username;
    string name;
    string last_name;
    string password;
    string email;

    while(getline(file, username, ',') && !found)
    {
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        if (username==username_search)
        {
            found = true;
            record.push_back(username);
            record.push_back(name);
            record.push_back(last_name);
            record.push_back(password);
            record.push_back(email);

        }
    }
        std::cout << record[0] << " " << record[1] << " "<< record[2] << " " << record[3] << " " << record[4] <<endl;
        return record;
}

//check if the username is in the database and its password matches, returns true if username is in there and password matches the specific username
bool checkPasswordandUsername(string file_name, string username, string password)
{
    vector<string> record;
    ifstream file;
    file.open(file_name);
    string one;
    string two;

    bool found = false;

    while(getline(file, one, ',') && !found)
    {
        getline(file, two, ',');
        if (one==username && two == password)
        {
            found = true;
        }
    }
        return found;

}

//changing email, password and username




}//std closed
