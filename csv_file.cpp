#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "csv_file.hpp"
// DATABASE CLASS

// constructor
Database::Database()
{
    this->file_name = "";
}
Database::Database(std::string file_name)
{
    this->file_name = file_name;
}

// registration, adding data to csv file, there are 6 parameters: randomly generated 4 digit id, username, name, last name, password and email (in this order)
bool Database ::writeDataToFile(std::string file_name, std::string username, std::string name, std::string last_name, std::string password, std::string email)
{
    std::ofstream file;
    file.open(file_name, std::ios_base::app);
    int number = rand() % 9000 + 1000;
    std::string id = std::to_string(number);
    file << id << ',' << username << ',' << name << ',' << last_name << ',' << password << ',' << email << std::endl;
    file.close();

    return true;
}

// looking for a username in a csv file and returning all data about it
std::vector<std::string> Database ::readRecordFromFile(std::string file_name, std::string username_search)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);

    bool found = false;
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (username == username_search)
        {
            found = true;
            record.push_back(id);
            record.push_back(username);
            record.push_back(name);
            record.push_back(last_name);
            record.push_back(password);
            record.push_back(email);
        }
    }
    if (found)
    {
        std::cout << record[0] << " " << record[1] << " " << record[2] << " " << record[3] << " " << record[4] << " " << record[5] << std::endl;
    }
    else
    {
        std::cout << "Username not found" << std::endl;
    }
    return record;
}

// check if the username is in the database and its password matches (for logging in)
bool Database::checkPasswordandUsername(std::string file_name, std::string username_given, std::string password_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (username_given == username && password_given == password)
        {
            found = true;
            std::cout << "Username and password match" << std::endl;
        }
    }
    if (!found)
    {
        std::cout << "Username and password do not match" << std::endl;
    }
    return found;
}

// change an email when given a username
bool Database::change_email(std::string file_name, std::string username_given, std::string password_given, std::string new_email)
{

    std::ofstream fout;
    fout.open("new1.csv", std::ios::out | std::ios::app);
    std::ifstream file;
    file.open(file_name);
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    bool found = false;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if (username_given == username && password_given == password)
        {
            found = true;
            fout << id << ',' << username << ',' << name << ',' << last_name << ',' << password << ',' << new_email << std::endl;
        }
        else
        {
            fout << id << ',' << username << ',' << name << ',' << last_name << ',' << password << ',' << email << std::endl;
        }
    }
    fout.close();
    file.close();

    // removing the existing file
    remove("new.csv");

    // renaming the updated file with the existing file name
    rename("new1.csv", "new.csv");

    return found;
}

// check if username is taken
bool Database::check_username(std::string file_name, std::string username_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;
    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        if (username_given == username)
        {
            found = true;
            std::cout << "username is taken" << std::endl;
        }
    }
    if (!found)
    {
        std::cout << "username is available" << std::endl;
    }
    return found;
}

// check if email is taken

bool Database::check_email(std::string file_name, std::string email_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;
    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (email_given == email)
        {
            found = true;
            std::cout << "email is taken" << std::endl;
        }
    }
    if (!found)
    {
        std::cout << "email is available" << std::endl;
    }
    return found;
}
// delete one user when given username and password
bool Database::delete_user(std::string file_name, std::string username_given, std::string password_given)
{
    std::ofstream fout;
    fout.open("new1.csv", std::ios::out | std::ios::app);
    std::ifstream file;
    file.open(file_name);
    std::string id;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    bool found = false;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if (username_given == username && password_given == password)
        {
            found = true;
        }
        else
        {
            fout << id << ',' << username << ',' << name << ',' << last_name << ',' << password << ',' << email << std::endl;
        }
    }
    fout.close();
    file.close();

    // removing the existing file
    remove("new.csv");

    // renaming the updated file with the existing file name
    rename("new1.csv", "new.csv");

    return found;
}

// deleting data from csv file
void Database::delete_data()
{
    std::ofstream ofs;
    ofs.open("new.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
