#ifndef CSV_HPP
#define CSV_HPP

#endif // CSV_HPP
#include <string>
#include <vector>
bool writeDataToFile(std::string file_name, std::string one, std::string two, std::string three);

std::vector<std::string> readRecordFromFile(std::string file_name, std::string search_term);
class Database
{
public:
    Database(); // Access the CSV file
    ~Database();
    bool writeDataToFile(std::string file_name, std::string one, std::string two, std::string three); // Add information to the CSV file
    std::vector<std::string> readRecordFromFile(std::string file_name, std::string search_term);
    ; // Read information from the CSV file
    bool checkPasswordandUsername(std::string file_name, std::string username, std::string password);
    void update_data(); // Updates the CSV file
    void delete_data(); // Deletes information from the CSV file

private:
    std::string datafile;
    std::string
};
