

// using namespace std;

// int main() {
//     cout << "Hello World!" << endl;
//     return 0;
// }

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "database.cpp"

int test_database()
{
    Database database("new.csv");

    // check if the file is empty bool empty = database.check_if_empty();

    // adding three users to the database
    bool writeFile = database.writeDataToFile("new.csv", "jsmith", "John", "Smith", "Giraffe13!!", "Giraffe13!!", "john.smith@yahoo.com");
    bool writeFile1 = database.writeDataToFile("new.csv", "emmax", "Emma", "Stone", "Peaceandlove567!", "Peaceandlove567!", "emma.stone@yahoo.com");
    bool writeFile2 = database.writeDataToFile("new.csv", "oskarty", "Oskar", "Tyrone", "oskarisnice", "oskarisnice", "oskar.tyrone@yahoo.com");
    bool writeFile3 = database.writeDataToFile("new.csv", "oskarttty", "Osktar", "Tyronte", "Oskaristnice123?", "Oskarisnice123?", "oskar.tyrone@yahtoo.com");

    std::cout << "working writeDataToFile" << std::endl;
    // checking whether the username is in there and returning all the info, last one says username not found
    std::vector<std::string> data = database.readRecordFromFile("new.csv", "jsmith");
    std::vector<std::string> data1 = database.readRecordFromFile("new.csv", "emmax");
    std::vector<std::string> data2 = database.readRecordFromFile("new.csv", "oskarty");
    std::vector<std::string> data3 = database.readRecordFromFile("new.csv", "beccac");
    std::cout << "working readRecordFromFile" << std::endl;

    // to log in, entering username and password, first three must match, last one says username or password is incorrect
    bool login = database.checkPasswordandUsername("new.csv", "jsmith", "Giraffe13!!");
    bool login1 = database.checkPasswordandUsername("new.csv", "emmax", "peace567");
    bool login2 = database.checkPasswordandUsername("new.csv", "oskarttty", "Oskaristnice123?");
    bool login3 = database.checkPasswordandUsername("new.csv", "beccac", "beccaisnice");
    std::cout << "working checkPasswordandUsername" << std::endl;

    // changing an email to existing users when given a username and a password
    bool change = database.change_email("new.csv", "jsmith", "Giraffe13!!", "john.smith@gmail.com");
    std::vector<std::string> data10 = database.readRecordFromFile("new.csv", "jsmith");
    std::cout << "working changeemail" << std::endl;

    // check if email is taken, first one should be taken, second one should not be taken as we have changed it above
    bool taken = database.check_email("new.csv", "john.smith@gmail.com");
    bool taken_old = database.check_email("new.csv", "john.smith@yahoo.com");
    std::cout << "working checkmail" << std::endl;

    // check if username is taken
    bool taken_username = database.check_username("new.csv", "jsmith");
    bool taken_username1 = database.check_username("new.csv", "emmax1");
    std::cout << "working check username" << std::endl;

    // deleting a user from the database
    bool delete_user = database.delete_user("new.csv", "jsmith", "giraffe1");
    std::cout << "working delete user" << std::endl;

    // deleting all the data from the database
    database.delete_data();
    std::cout << "working ALL" << std::endl;
    return 0;
}
