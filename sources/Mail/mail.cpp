#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>


int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Failed to create socket" << std::endl;
    return 1;
  }

  // Connect to the SMTP server
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(587);  // 587 is the default SMTP port
  inet_pton(AF_INET, "smtp.gmail.com", &addr.sin_addr);
  if (connect(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
    std::cerr << "Failed to connect to SMTP server" << std::endl;
    return 1;
  }

  // Send the SMTP commands to send the email
  std::string message =
    "EHLO localhost\r\n"
    "MAIL FROM: <systemauthentification@gmail.com>\r\n"
    "RCPT TO: <sophieclaireantoun@gmail.com>\r\n"
    "DATA\r\n"
    "From: systemauthentification@gmail.com\r\n"
    "To: sophieclaireantoun@gmail.com\r\n"
    "Subject: Test email\r\n"
    "\r\n"
    "This is a test email.\r\n"
    ".\r\n"
    "QUIT\r\n";
  if (send(sockfd, message.data(), message.size(), 0) < 0) {
    std::cerr << "Failed to send message" << std::endl;
    return 1;
  }

  // Close the socket
  close(sockfd);

  std::cout << "Email sent successfully" << std::endl;
  return 0;
}


