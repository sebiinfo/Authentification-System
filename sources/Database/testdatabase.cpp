#include "database.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main()
{
    Database database("new.csv");
    // database.delete_data();

    // check if the file is empty
    bool empty = database.check_if_empty();
    cout << "File is " << (empty ? "" : "not ") << "empty" << endl;

    // adding three users to the database
    /* database.writeDataToFile("johnsmith", "Johna", "Smithe", "Giraffe13!!",
                             "Giraffe13!!", "john@yahoo.com"); */
    database.writeDataToFile("emmax", "Emma", "Stone", "Peaceandlove567!",
                             "Peaceandlove567!", "emma.stone@yahoo.com");
    database.writeDataToFile("oskarty", "Oskar", "Tyrone", "oskarisnice",
                             "oskarisnice", "oskar.tyrone@yahoo.com");
    database.writeDataToFile("oskarttty", "Osktar", "Tyronte",
                             "Oskarisnice123?", "Oskarisnice123?",
                             "oskar.tyrone@yahtoo.com");
    // password requirements
    Database::Possible_Errors a = database.writeDataToFile("oskarty", "Oskar", "Tyrone", "oskarisnice",
                                                           "oskarisnice", "oskar.tyrone@yahoo.com");
    std::cout << a << std::endl;
    // taken username
    Database::Possible_Errors b = database.writeDataToFile("emmax", "Emma", "Xavier", "Authentication567!", "Authentication567!", "emma.x@yahoo.com");
    std::cout << b << std::endl;
    // taken email
    Database::Possible_Errors c = database.writeDataToFile("johnana1", "Johnana", "Smirth", "Password546!", "Password546!", "john@yahoo.com");
    std::cout << c << std::endl;

    // checking whether the username is in there and returning all the info,
    // last one says username not found
    std::vector<std::string> data = database.readRecordFromFile("oskarttty");
    // to log in, entering username and password, first three must match, last
    // one says username or password is incorrect
    bool login = database.checkPasswordandUsername("jsmith", "Giraffe13!!");
    // changing an email to existing users when given a username and a password
    bool change =
        database.change_email("jsmith", "Giraffe13!!", "john.smith@gmail.com");
    // check if email is taken, first one should be taken, second one should not
    // be taken as we have changed it above
    bool taken = database.check_email("john.smith@gmail.com");
    // check if username is taken
    bool taken_username = database.check_username("jsmith");
    // deleting a user from the database
    bool delete_user = database.delete_user("jsmith", "Giraffe13!!");
    // deleting all the data from the database
    // database.delete_data();
}
