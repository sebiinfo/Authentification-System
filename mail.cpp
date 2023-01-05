#include "mail.hpp"
#include <iostream>
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;

SMTPClient::SMTPClient() :
   ...
  , sslContext_(service_, asio::ssl::context::sslv3)
  , sslSocket_(service, sslContext_)
  , socket_(sslSocket_.next_layer()) {
}
void SMTPClient::connect(const std::string& hostname, unsigned short port) {
   boost::system::error_code error = boost::asio::error::host_not_found;
   boost::asio::ip::tcp::resolver resolver(service_);
   boost::asio::ip::tcp::resolver::query query(hostname, boost::lexical_cast<std::string>(port));
   boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
   boost::asio::ip::tcp::resolver::iterator end;

   while (error && endpoint_iterator != end) {
      socket_.close();
      socket_.connect(*endpoint_iterator++, error);
   }

   if (error) {
      std::cerr << "error: " << error.message());
   } else {
      handshake();
   }
}

void SMTPClient::handshake() {
  // Receiving the server identification
  std::string serverName = socket_.remote_endpoint().address().to_string();
  if (tlsEnabled_) {
    boost::system::error_code error;
    tlsEnabled_ = false;
    serverId_ = read(Ready);
    message_ << "EHLO " << serverName << "\r\n";
    write();
    read();
    message_ << "STARTTLS" << "\r\n";
    write();
    read(Ready);
    sslSocket_.handshake(SslSocket::client, error);
    if (error) {
      std::cerr << "Handshake error: " << error.message());
    }
    tlsEnabled_ = true;
  } else {
    serverId_ = read(Ready);
  }
  message_ << "EHLO " << serverName << "\r\n";
  write();
  read();
}