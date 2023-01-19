#define CAMERA 1

#if CAMERA == 1

#include <QApplication>
#include <camera.h>
#include <iostream>
#include <QFile>
#include <database.hpp>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Camera camera;
    camera.show();
    QFile styleSheetFile("C:\\Users\\paula\\Downloads\\Telegram Desktop\\stylesheet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);
    return app.exec();

};



#elif CAMERA == 0

#include "mail.hpp"
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureSMTPClientSession.h>

using namespace std;

int main() {
    cout << "start" << endl;
    Poco::Net::MailMessage msg;
    msg.addRecipient(
        Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT,
                                 "sophieclaireantoun0@gmail.com", "Sophie"));
    msg.setSender("Me <sophieclaireantoun0@gmail.com>");
    msg.setSubject("Test");
    msg.setContent("Content");

    Poco::Net::SMTPClientSession smtp("smtp-relay.gmail.com", 465);
    try {
        smtp.login(Poco::Net::SMTPClientSession::LoginMethod::AUTH_LOGIN,
                   "sophieclaireantoun0@gmail.com", "tnofcyabsptdsqrc");
        smtp.sendMessage(msg);
    } catch (Poco::Net::SMTPException e) {
        cout << e.message() << endl;
    }

    //                "tnofcyabsptdsqrc");

    smtp.close();
    cout << "stop" << endl;
    return 0;
}

#endif
