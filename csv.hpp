#ifndef CSV_HPP
#define CSV_HPP

#endif // CSV_HPP
#include <string>
#include <vector>




bool writeDataToFile(std::string file_name, std::string one, std::string two, std::string three);

std::vector<std::string> readRecordFromFile(std::string file_name, std::string search_term);

