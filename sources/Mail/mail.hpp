#include <iostream>
#include <cstdlib>
#include <ctime>

class Mail {
public:
    int generateRandomNumber();
    void send_mail(int random_generated, std::string adress);
    std::string generatemessage(int random_generated);
    int get_random(){return randomgenerated;};
    bool verification(int userInput);
    bool verifyNumber(int random_generated, int userInput);
    std::string mail(std::string adress);
private:
    int randomgenerated;

};
