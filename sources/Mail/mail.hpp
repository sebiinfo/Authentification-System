#include <iostream>
#include <cstdlib>
#include <ctime>

class Mail {
public:
    Mail() = default;

    int generateRandomNumber();
    void send_mail(std::string adress, std::string messagecontent);
    std::string generatemessage(int random_generated);
    int get_random(){return randomgenerated;};
    bool verifyNumber(int code_sent, int code_entered);
    int mail(std::string adress);
private:
    int randomgenerated;
};
