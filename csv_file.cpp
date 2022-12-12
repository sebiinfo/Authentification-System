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

// registration, adding data to csv file, there are 5 parameters: username, name, last name, password and email (in this order)
bool Database ::writeDataToFile(std::string file_name, std::string username, std::string name, std::string last_name, std::string password, std::string email)
{
    std::ofstream file;
    file.open(file_name, std::ios_base::app);
    file << username << ',' << name << ',' << last_name << ',' << email << ',' << password << std::endl;
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
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    while (getline(file, username, ',') && !found)
    {
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (username == username_search)
        {
            found = true;
            record.push_back(username);
            record.push_back(name);
            record.push_back(last_name);
            record.push_back(password);
            record.push_back(email);
        }
    }
    std::cout << record[0] << " " << record[1] << " " << record[2] << " " << record[3] << " " << record[4] << std::endl;
    return record;
}

// check if the username is in the database and its password matches (for logging in)
bool Database::checkPasswordandUsername(std::string file_name, std::string username_given, std::string password_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;

    bool found = false;

    while (getline(file, username, ',') && !found)
    {
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (username_given == username && password_given == password)
        {
            found = true;
        }
    }
    return found;
}

// changing email, password and username
// generates a new password and set it as new password for the username and email
// enter username and password, then you can change the corresponding email

bool Database::change_email(std::string file_name, std::string username_given, std::string password_given, std::string new_email)
{
    std::vector<std::string> record;
    bool success = false;
    std::ifstream file;
    file.open(file_name);

    if (checkPasswordandUsername(file_name, username_given, password_given))
    {
        // can I make it return boolean and the data?
        record = readRecordFromFile(file_name, username_given);
        record.at(-1) = new_email; // check if works
        success = true;
    }
    std::cout << success << std::endl; // print out if the email was changed
    std::cout << record[0] << " " << record[1] << " " << record[2] << " " << record[3] << " " << record[4] << std::endl;
    return success;
}
// check if username is taken
bool Database::check_username(std::string file_name, std::string username_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;
    bool found = false;

    while (getline(file, username, ',') && !found)
    {
        if (username_given == username)
        {
            found = true;
        }
    }
    return found;
}
// check if email is taken

bool Database::check_email(std::string file_name, std::string email_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;
    bool found = false;

    while (getline(file, username, ',') && !found)
    {
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, '\n');
        if (email_given == email)
        {
            found = true;
        }
    }
    return found;
}
// delete one user
// a new class for user information and as input functions take user information

// deleting data from csv file
void Database::delete_data()
{
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
