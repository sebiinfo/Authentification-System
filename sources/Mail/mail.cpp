#include "mail.hpp"
#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>

int main() {
Poco::Net::MailMessage msg;
msg.addRecipient (Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT,"bob@example.com", "Bob"));
msg.setSender ("Me <me@example.com>");
msg.setSubject ("Subject");
msg.setContent ("Content");

Poco::Net::SMTPClientSession smtp ("mail.example.com");
smtp.login ();
smtp.sendMessage (msg);
smtp.close ();

return 0;
}
