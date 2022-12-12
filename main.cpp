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
#include "csv_file.hpp"

int main()
{
   Database database("new.txt");

   bool writeFile = database.writeDataToFile("new.txt", "John", "Smith", "jsmith", "giraffe1", "john.smith@yahoo.com");

   std::vector<std::string> data = database.readRecordFromFile("new.txt", "password");

   return 0;
}
