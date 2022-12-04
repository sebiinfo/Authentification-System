#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace std{


bool writeDataToFile(string file_name, string one, string two, string three);

vector<string> readRecordFromFile(string file_name, string search_term);



int test1(){
    bool writeFile = writeDataToFile("new.txt", "username", "password", "date");

    return 0;
}

int test2(){
    vector<string> data = readRecordFromFile("new.txt", "password");
    return 0;
}
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
    std::cout << record[0] << " " << record[1] << " "<< record[2] <<endl;
    return record;
}
}
