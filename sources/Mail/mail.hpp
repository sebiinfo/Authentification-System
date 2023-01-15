#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/MailMessage.h>

class SMTPClientSession
{
public:
    // typedefs

    typedef std::vector<std::string> Recipients;

    // enums

    enum
    {
        SMTP_PORT = 25,
    };

    // construction

    SMTPClientSession(const Poco::Net::StreamSocket& socket);

    SMTPClientSession(
        const std::string& host,
        Poco::UInt16 port = SMTP_PORT
        );

    // methods

    void
    setTimeout(const Poco::Timespan& timeout);

    Poco::Timespan
    getTimeout() const;

    void
    login(const std::string& hostname);

    void
    login();

    void
    login(
        const std::string& hostname,
        Poco::Net::SMTPClientSession::LoginMethod loginMethod,
        const std::string& username,
        const std::string& password
        );

    void
    login(
        Poco::Net::SMTPClientSession::LoginMethod loginMethod,
        const std::string& username,
        const std::string& password
        );

    void
    open();

    void
    close();

    void
    sendMessage(const Poco::Net::MailMessage& message);

    void
    sendMessage(
        const Poco::Net::MailMessage& message,
        const Recipients& recipients
        );

    void
    sendMessage(std::istream& istr);

    int
    sendCommand(
        const std::string& command,
        std::string& response
        );

    int
    sendCommand(
        const std::string& command,
        const std::string& arg,
        std::string& response
        );

    void
    sendAddresses(
        const std::string& from,
        const Recipients& recipients
        );

    void
    sendData();

protected:

    void
    login(
        const std::string& hostname,
        std::string& response
        );

    Poco::Net::DialogSocket&
    socket();
};


class MailRecipient
{
public:


    // construction

    MailRecipient();
    MailRecipient(const MailRecipient& recipient);

    MailRecipient(
            Poco::Net::MailRecipient::RecipientType type,
        const std::string& address
        );

    MailRecipient(
            Poco::Net::MailRecipient::RecipientType type,
        const std::string& address,
        const std::string& realName
        );

    // methods

    MailRecipient&
    operator=(const MailRecipient& recipient);

    void
    swap(MailRecipient& recipient);

    Poco::Net::MailRecipient::RecipientType
    getType() const;

    void
    setType(Poco::Net::MailRecipient::RecipientType type);

    const std::string&
    getAddress() const;

    void
    setAddress(const std::string& address);

    const std::string&
    getRealName() const;

    void
    setRealName(const std::string& realName);
};
