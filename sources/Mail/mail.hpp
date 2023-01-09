#include <iostream>
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;

 public ref class SmtpClient : IDisposable

/*
 * \brief response codes from host
 */
enum RessultCode {
  Okay = 250,
  Data = 354,
  Ready = 220,
  Goodbye = 221,
  Accepted = 334,
  AUTH_successful = 235
};

class SMTPClient {
  public: 
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SslSocket;
  ...
  private:
    std::string                   serverId_;
    std::stringstream             message_;
    boost::asio::io_service       service_;
    boost::asio::ssl::context     sslContext_;
    SslSocket                     sslSocket_;
    boost::asio::ip::tcp::socket& socket_;
    bool                          tlsEnabled_;
    void connect(const std::string &hostname, unsigned short port);
};
