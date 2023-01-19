

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
    bool writeFile = database.writeDataToFile("jsmith", "John", "Smith", "Giraffe13!!", "Giraffe13!!", "john.smith@yahoo.com");
    bool writeFile1 = database.writeDataToFile("emmax", "Emma", "Stone", "Peaceandlove567!", "Peaceandlove567!", "emma.stone@yahoo.com");
    bool writeFile2 = database.writeDataToFile("oskarttty", "Osktar", "Tyronte", "Oskarisnice123?", "Oskarisnice123?", "oskar.tyrone@yahtoo.com");

    //checking the cases where the user should not be added
    bool writeFile3 = database.writeDataToFile("jsmith", "Jason", "Smith", "Elephant134!", "Elephant134!", "jason.smith@yahoo.com");
    bool writeFile4 = database.writeDataToFile("oskarty", "Oskar", "Tyrone", "oskarisnice", "oskarisnice", "oskar.tyrone@yahoo.com");
    bool writeFile5 = database.writeDataToFile("emmax123", "Emma", "Stone", "Allisgood54?", "Allisgood54?", "emma.stone@yahoo.com");
    bool writeFile6 = database.writeDataToFile("ritaby", "Rita", "Bylone", "Iamhungry65*", "Imhungry65*", "rita.byrone@gmail.com");


    std::cout << "working writeDataToFile" << std::endl;
    // checking whether the username is in there and returning all the info, last one says username not found
    std::vector<std::string> data = database.readRecordFromFile("jsmith");
    std::vector<std::string> data1 = database.readRecordFromFile("emmax");
    std::vector<std::string> data2 = database.readRecordFromFile("oskarty");
    std::vector<std::string> data3 = database.readRecordFromFile("beccac");
    std::cout << "working readRecordFromFile" << std::endl;

    // to log in, entering username and password, first three must match, last one says username or password is incorrect
    bool login = database.checkPasswordandUsername("jsmith", "Giraffe13!!");
    bool login1 = database.checkPasswordandUsername("emmax", "peace567");
    bool login2 = database.checkPasswordandUsername("oskarttty", "Oskaristnice123?");
    bool login3 = database.checkPasswordandUsername("beccac", "beccaisnice");
    std::cout << "working checkPasswordandUsername" << std::endl;

    // changing an email to existing users when given a username and a password
    bool change = database.change_email("jsmith", "Giraffe13!!", "john.smith@gmail.com");
    std::vector<std::string> data10 = database.readRecordFromFile("jsmith");
    std::cout << "working changeemail" << std::endl;

    // check if email is taken, first one should be taken, second one should not be taken as we have changed it above
    bool taken = database.check_email("john.smith@gmail.com");
    bool taken_old = database.check_email("john.smith@yahoo.com");
    std::cout << "working checkmail" << std::endl;

    // check if username is taken
    bool taken_username = database.check_username("jsmith");
    bool taken_username1 = database.check_username("emmax1");
    std::cout << "working check username" << std::endl;

    // deleting a user from the database
    bool delete_user = database.delete_user("jsmith", "giraffe1");
    std::cout << "working delete user" << std::endl;

    // deleting all the data from the database
    // database.delete_data();
    std::cout << "working ALL" << std::endl;
    return 0;
}
