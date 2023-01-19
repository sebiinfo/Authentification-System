#include <iostream>
#include <cstdlib>
#include <ctime>

class Mail {
public:
    int generateRandomNumber();
    void mail(int random_generated, std::string adress, std::string messagecontent);
    void generatemessage(int random_generated);
    int get_random(){return randomgenerated;};
    bool verification(int userInput);
    bool verifyNumber(int random_generated, int userInput);
private:
    int randomgenerated;

};
