#include "mail.hpp"
#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/MailMessage.h>
//#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <random>


void mail() {
Poco::Net::MailMessage msg;
msg.addRecipient (Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT,"sophieclaireantoun0@gmail.com", "Sophie"));
msg.setSender ("Me <sophieclaireantoun0@gmail.com>");
msg.setSubject ("Test");
msg.setContent ("Content");

Poco::Net::SMTPClientSession smtp ("smtp.gmail.com", 465);
smtp.login (    Poco::Net::SMTPClientSession::LoginMethod::AUTH_PLAIN,
                "sophieclaireantoun0@gmail.com",
                "tnofcyabsptdsqrc");
//                "tnofcyabsptdsqrc");
//smtp.sendMessage (msg);
smtp.close ();
}



void Randomnumber::generaterandom() {
    std::random_device rd; //create a random device
    std::mt19937; gen(rd()); //create a Mersenne Twister generator
    std::uniform_int_distribution<> dis(10000, 99999); //create a distribution for 5-digit numbers
    int randomNum = dis(gen); //generate a random 5-digit number
    randomnumber=randomNum;
}

bool Randomnumber::checkifsame(){
    int userInput;
    std::cout << "Almost there! We sent you an email with a 5-digit number. Please enter it for verification: ";
    std::cin >> userInput;
    if (userInput == randomnumber) {
        std::cout << "Congratulations! You have will be able to reset your password." << std::endl;
        return true;
    } else {
        std::cout << "Sorry, that is not the correct number, please try again." << std::endl;
        return false;
    }
}
