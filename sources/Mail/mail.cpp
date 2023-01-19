#include "mail.hpp"
#include <iostream>
#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;
using Poco::Net::SMTPClientSession;
using Poco::Net::SecureSMTPClientSession;
using Poco::Net::StringPartSource;
using Poco::Net::SSLManager;
using Poco::Net::Context;
using Poco::Net::KeyConsoleHandler;
using Poco::Net::PrivateKeyPassphraseHandler;
using Poco::Net::InvalidCertificateHandler;
using Poco::Net::ConsoleCertificateHandler;
using Poco::SharedPtr;
using Poco::Path;
using Poco::Exception;

class SSLInitializer
{
public:
    SSLInitializer()
    {
        Poco::Net::initializeSSL();
    }

    ~SSLInitializer()
    {
        Poco::Net::uninitializeSSL();
    }
};


int generateRandomNumber() {
    srand(time(0));
    int randomNumber = arc4random() % 99999 + 10000; // generates a random number between 10000 and 99999
    return randomNumber;
}

bool verifyNumber(int random_generated, int userInput) {
    int randomNumber = random_generated;
    if (userInput == randomNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool verification(int random_generated){
    int userInput;
    std::cout << "Enter a 5-digit number: ";
    std::cin >> userInput;
    if (verifyNumber(random_generated, userInput)) {
        std::cout << "Congratulations! You entered the correct number." << std::endl;
        return true;
    }
    else {
        std::cout << "Sorry, that is not the correct number." << std::endl;
        return false;
    }
}

void mail(int random_generated, std::string adress){

    cout << "start" << endl;
    SSLInitializer sslInitializer;

    Poco::Net::MailMessage msg;
    Poco::SharedPtr< Poco::Net::InvalidCertificateHandler> pCert = new ConsoleCertificateHandler(false);
    Context::Ptr pContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

    std::cout << "SSLManager::instance()" << std::endl;
    SSLManager::instance().initializeClient(0, pCert, pContext);

    msg.addRecipient (Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, adress, "Sophie"));
    msg.setSender ("Me <systemauthentifications@gmail.com>");
    msg.setSubject ("Your password verification code");
    int x = 5;
    std::string messagecontent = "Hello!\nHere is the 5-digits code that you will need in order to reinitialize your password!\nDo not share is with anyone.\nYour code is: ";
    messagecontent += std::to_string(random_generated);
    msg.setContent (messagecontent);
    cout << "stop1" << endl;
    std::string host = "smtp.google.com";
    int port = 465;
//    Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SecureSMTPClientSession smtp("smtp.gmail.com", 587);
    cout << "stop2" << endl;
        cout << "login" << endl;
        smtp.open();
        smtp.login();
        cout << "startTLS" << endl;
        Poco::Net::initializeSSL();
        smtp.startTLS(pContext);
        cout << "login 2" << endl;
        smtp.login (    Poco::Net::SecureSMTPClientSession::LoginMethod::AUTH_LOGIN,
                        "systemauthentification@gmail.com",
                        "seqmqmkmyczkbhyz");
        smtp.sendMessage (msg);


    smtp.close ();
    cout << "stop3" << endl;

}
