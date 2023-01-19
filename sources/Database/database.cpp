#include "database.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// DATABASE CLASS

// constructor
Database::Database()
{
    this->file_name = "new.csv";
    this->profile = Profile();
}
Database::Database(std::string file_name) : Database()
{
    this->file_name = file_name;
}

// check if the csv file is empty
bool Database::check_if_empty()
{
    std::ifstream file;
    file.open(file_name);
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// registration, adding data to csv file, there are 6 parameters: unique id
// (users are ordered), username, name, last name, password, email, salt (in
// this order) checks the password twice whether the input is the same returns
// true if the data was successfully added to the database
// 0 = successful_login; 1 = password_confirm_password; 2 = email_taken; 3 = username_taken; 4 = password_requirements
Database::Possible_Errors Database::writeDataToFile(
    std::string username, std::string name, std::string last_name,
    std::string password, std::string confirm_password,
    std::string email)
{ // if password meets all length and character
  // requirements, if username and email are not taken
  // and password and confirm_password matches

    if (!profile.validate_password(password))
    {
        return password_requirements;
    }
    if ((check_username(username)))
    {
        return username_taken;
    }
    if ((check_email(email)))
    {
        return email_taken;
    }
    else
    {

        std::ifstream file;
        file.open(file_name);
        int number = 0;
        std::string id1;
        std::string id;
        std::string line;

        while (getline(file, line))
        {
            id1 = line.substr(0, line.find(','));
            std::stringstream ss(id1);
            ss >> number;
        }
        number = number + 1;
        file.close();
        id = std::to_string(number);
        std::ofstream file1;
        file1.open(file_name, std::ios::app);
        profile.generate_salt();
        std::vector<std::string> encrypted_password_salt =
            profile.build_profile(username, password, confirm_password);
        if (!encrypted_password_salt.empty())
        {

            file1 << id << ',' << username << ',' << name << ',' << last_name
                  << ',' << encrypted_password_salt[0] << ',' << email << ','
                  << encrypted_password_salt[1] << std::endl;
            file1.close();
        }
        else
        {
            file1.close();
            return password_confirm_password;
        }
    }
    return successful_login;
}

// looking for a username in a csv file and returning all data about it
std::vector<std::string>
Database ::readRecordFromFile(std::string username_search)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);

    std::string id;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');
        if (username == username_search)
        {
            record.push_back(id);
            record.push_back(username);
            record.push_back(name);
            record.push_back(last_name);
            record.push_back(password);
            record.push_back(email);
            record.push_back(salt);
        }
    }
    return record;
}

// looking for a username in a csv file and returning all data about it
std::vector<std::string>
Database ::readRecordFromFile(std::string username_search)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);

    std::string id;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');
        if (username == username_search)
        {
            record.push_back(id);
            record.push_back(username);
            record.push_back(name);
            record.push_back(last_name);
            record.push_back(password);
            record.push_back(email);
            record.push_back(salt);
        }
    }
    return record;
}

// check if the username is in the database and its password matches (for
// logging in)
bool Database::checkPasswordandUsername(std::string username_given,
                                        std::string password_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;

    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');
        if (username_given == username)
        {
            if (profile.compare_password(username_given, password_given,
                                         password, salt))
            {
                found = true;
                // std::cout << "Username and password match" << std::endl;
            }
        }
    }

    if (!found)
    {
        // std::cout << "Username and password do not match" << std::endl;
    }
    return found;
}

// change an email when given a username
bool Database::change_email(std::string username_given,
                            std::string password_given, std::string new_email)
{

    std::ofstream fout;
    fout.open("new1.csv", std::ios::out | std::ios::app);
    std::ifstream file;
    file.open(file_name);
    std::string id;

    bool found = false;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');

        if ((username_given == username) &&
            (profile.compare_password(username_given, password_given, password,
                                      salt)))
        {
            found = true;
            fout << id << ',' << username << ',' << name << ',' << last_name
                 << ',' << password << ',' << new_email << ',' << salt
                 << std::endl;
        }
        else
        {
            fout << id << ',' << username << ',' << name << ',' << last_name
                 << ',' << password << ',' << email << ',' << salt << std::endl;
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

// change password when given a username and a password
bool Database::change_password(std::string username_given,
                               std::string password_given,
                               std::string new_password,
                               std::string confirm_new_password)
{

    std::ofstream fout;
    fout.open("new1.csv", std::ios::out | std::ios::app);
    std::ifstream file;
    file.open(file_name);
    std::string id;

    bool found = false;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');

        if ((username_given == username) &&
            (profile.compare_password(username_given, password_given, password,
                                      salt)))
        {
            found = true;
            std::vector<std::string> new_vector = profile.change_password(
                username, new_password, confirm_new_password);
            fout << id << ',' << username << ',' << name << ',' << last_name
                 << ',' << new_vector[0] << ',' << email << ',' << new_vector[1]
                 << std::endl;
        }
        else
        {
            fout << id << ',' << username << ',' << name << ',' << last_name
                 << ',' << password << ',' << email << ',' << salt << std::endl;
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
bool Database::check_username(std::string username_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;
    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');
        if (username_given == username)
        {
            found = true;
            // std::cout << "username is taken" << std::endl;
        }
    }
    if (!found)
    {
        // std::cout << "username is available" << std::endl;
    }
    return found;
}

// check if email is taken
bool Database::check_email(std::string email_given)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);
    std::string id;
    bool found = false;

    while (getline(file, id, ',') && !found)
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');
        if (email_given == email)
        {
            found = true;
            // std::cout << "email is taken" << std::endl;
        }
    }
    if (!found)
    {
        // std::cout << "email is available" << std::endl;
    }
    return found;
}
// delete one user when given username and password
bool Database::delete_user(std::string username_given,
                           std::string password_given)
{
    std::ofstream fout;
    fout.open("new1.csv", std::ios::out | std::ios::app);
    std::ifstream file;
    file.open(file_name);
    std::string id;

    bool found = false;
    while (getline(file, id, ','))
    {
        getline(file, username, ',');
        getline(file, name, ',');
        getline(file, last_name, ',');
        getline(file, password, ',');
        getline(file, email, ',');
        getline(file, salt, '\n');

        if (username_given == username &&
            profile.compare_password(username_given, password_given, password,
                                     salt))
        {
            found = true;
        }
        else
        {
            fout << id << ',' << username << ',' << name << ',' << last_name
                 << ',' << password << ',' << email << ',' << salt << std::endl;
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

//....................................................User_Input
// class.......................................................
/*
// constructor
// User_Input::User_Input() { this->file_name = ""; }
// User_Input::User_Input(std::string file_name) { this->file_name = file_name;
}

// // add information to csv file with given username
// bool User_Input::add_data(std::string file_name) {
//     Database database(file_name);
//     std::ofstream fout;
//     fout.open("new1.csv", std::ios::out | std::ios::app);
//     std::ifstream file;
//     file.open(file_name);
//     std::string id;
//     std::string username;
//     std::string name;
//     std::string last_name;
//     std::string password;
//     std::string email;
//     std::string salt;
//     std::string username_given;
//     std::string password_given;
//     bool found = false;
//     std::cout << "Enter your username: ";
//     std::cin >> username_given;
//     std::cout << "Enter your password: ";
//     std::cin >> password_given;
//     if (database.checkPasswordandUsername(file_name, username_given,
//                                           password_given)) {
//         std::string hobbies;
//         std::cout << "Enter your hobbies: ";
//         std::cin >> hobbies;
//         // if there is a comma in the user input of hobbies, replace it with
a
//         // semicolon so that it would not be a separate entry in a csv file
//         for (int i = 0; i < hobbies.length(); i++) {
//             if (hobbies[i] == ',') {
//                 hobbies[i] = ';';
//             }
//         }

//         while (getline(file, id, ',')) {
//             getline(file, username, ',');
//             getline(file, name, ',');
//             getline(file, last_name, ',');
//             getline(file, password, ',');
//             getline(file, email, ',');
//             getline(file, salt, '\n');

//             if (username_given == username && password_given == password) {
//                 found = true;
//                 fout << id << ',' << username << ',' << name << ',' <<
last_name
//                      << ',' << password << ',' << email << ',' << salt << ','
//                      << hobbies << std::endl;
//             } else {
//                 fout << id << ',' << username << ',' << name << ',' <<
last_name
//                      << ',' << password << ',' << email << ',' << salt
//                      << std::endl;
//             }
//         }
//         fout.close();
//         file.close();

//         // removing the existing file
//         remove("new.csv");

//         // renaming the updated file with the existing file name
//         rename("new1.csv", "new.csv");
//     }
//     // if the user did not succeed to authenticate
//     else {
//         std::cout << "Username or password is incorrect" << std::endl;
//     }

    return found;
}
*/

// check if confirm password = password
// bool Database::check_confirm_password(std::string password, std::string
// confirm_password)
// {
//     if (password == confirm_password)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }
