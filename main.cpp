//#include <iostream>

// using namespace std;

// int main() {
//     cout << "Hello World!" << endl;
//     return 0;
// }

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <csv_file.cpp>

int main()
{
   bool writeFile = std::writeDataToFile("new.txt", "username1", "password1", "date1");

   std::vector<std::string> data = readRecordFromFile("new.txt", "password");



   return 0;
}
