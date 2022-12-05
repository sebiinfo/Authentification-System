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
bool writeDataToFile(string file_name, string one, string two, string three){
    std::ofstream file;
    file.open(file_name, ios_base::app);
    file << one << ',' << two << ',' << three << endl;
    file.close();

    return true;
}

//looking for a username in a csv file and returning all data about it
vector<string> readRecordFromFile(string file_name, string search_term){
    vector<string> record;
    ifstream file;
    file.open(file_name);

    bool found = false;
    string one;
    string two;
    string three;

    while(getline(file, one, ',') && !found)
    {
        getline(file, two, ',');
        getline(file, three, '\n');
        if (one==search_term)
        {
            found = true;
            record.push_back(one);
            record.push_back(two);
            record.push_back(three);
        }
    }
        //std::cout << record[0] << " " << record[1] << " "<< record[2] <<endl;
        return record;
}

//check if the username is in the database and its password matches
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
        //std::cout << record[0] << " " << record[1] << " "<< record[2] <<endl;
        return found;

}

}//std closed

