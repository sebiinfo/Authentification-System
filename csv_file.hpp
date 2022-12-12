#ifndef CSV_HPP
#define CSV_HPP

#endif // CSV_HPP
#include <string>
#include <vector>
// right now to include functions of csv file
class Database
{
public:
    Database();
    Database(std::string file_name);                                                                                                                     // Access the CSV file
    bool writeDataToFile(std::string file_name, std::string username, std::string name, std::string last_name, std::string password, std::string email); // Add information to the CSV file
    std::vector<std::string> readRecordFromFile(std::string file_name, std::string username_search);                                                     // Read information from the CSV file, print all records
    bool checkPasswordandUsername(std::string file_name, std::string username_given, std::string password_given);
    bool check_username(std::string file_name, std::string username_given);
    bool check_email(std::string file_name, std::string email_given);                                                        // Check if the username and password are correct, matching
    bool change_email(std::string file_name, std::string username_given, std::string password_given, std::string new_email); // change email account was registered with
    void delete_data();                                                                                                      // Deletes information from the CSV file

private:
    std::string file_name;
    std::string username;
    std::string name;
    std::string last_name;
    std::string password;
    std::string email;
    std::string search_term;
    std::string new_email;
};
