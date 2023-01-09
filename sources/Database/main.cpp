// #include <iostream>

// using namespace std;

// int main() {
//     cout << "Hello World!" << endl;
//     return 0;
// }

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include "csv_file.cpp"
#include "../Password/password.cpp"

int main()
{
   Database database("new.csv");
<<<<<<< HEAD
   User_Input user_input("new.csv");
=======
   Profile p = Profile();
>>>>>>> 2f7292370065de63318affec223e3446aeece63d

   // check if the file is empty
   // bool empty = database.check_if_empty("new.csv");

   // adding three users to the database
   // bool writeFile = database.writeDataToFile("new.csv", "jsmith", "John", "Smith", "giraffe1", "john.smith@yahoo.com");
   // bool writeFile1 = database.writeDataToFile("new.csv", "emmax", "Emma", "Stone", "peace567", "emma.stone@yahoo.com");
   // bool writeFile2 = database.writeDataToFile("new.csv", "oskarty", "Oskar", "Tyrone", "oskarisnice", "oskar.tyrone@yahoo.com");
   // bool writeFile3 = database.writeDataToFile("new.csv", "oskarttty", "Osktar", "Tyronte", "oskaristnice", "oskar.tyrone@yahtoo.com");

   // // checking whether the username is in there and returning all the info, last one says username not found
   // std::vector<std::string> data = database.readRecordFromFile("new.csv", "jsmith");
   // std::vector<std::string> data1 = database.readRecordFromFile("new.csv", "emmax");
   // std::vector<std::string> data2 = database.readRecordFromFile("new.csv", "oskarty");
   // std::vector<std::string> data3 = database.readRecordFromFile("new.csv", "beccac");

   // // to log in, entering username and password, first three must match, last one says username or password is incorrect
   // bool login = database.checkPasswordandUsername("new.csv", "jsmith", "giraffe1");
   // bool login1 = database.checkPasswordandUsername("new.csv", "emmax", "peace567");
   // bool login2 = database.checkPasswordandUsername("new.csv", "oskarty", "oskarisnice");
   // bool login3 = database.checkPasswordandUsername("new.csv", "beccac", "beccaisnice");

   // changing an email to existing users when given a username and a password
   // bool change = database.change_email("new.csv", "jsmith", "giraffe1", "john.smith@gmail.com");

   // check if email is taken, first one should be taken, second one should not be taken as we have changed it above
   // bool taken = database.check_email("new.csv", "john.smith@gmail.com");
   // bool taken_old = database.check_email("new.csv", "john.smith@yahoo.com");

   // check if username is taken
   // bool taken_username = database.check_username("new.csv", "jsmith");
   // bool taken_username1 = database.check_username("new.csv", "emmax1");

   // deleting a user from the database
   // bool delete_user = database.delete_user("new.csv", "jsmith", "giraffe1");

   // user_input testing
   bool adding = user_input.add_data("new.csv");

   // deleting all the data from the database
   // database.delete_data();

   return 0;
}
