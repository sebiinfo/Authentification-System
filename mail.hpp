#include <iostream>
#include <string>
#include <openssl/ssl.h>
#include <openssl/bio.h>

using namespace std;

// SMTP class
class SMTP {
    private:
        // SSL context and connection
        SSL_CTX *ctx;
        SSL *ssl;
        BIO *bio;

        // Server details
        string server;
        int port;
        string username;
        string password;

        // Private functions
        void send(const string &);
        void recv();

    public:
        // Constructor
        SMTP(const string &server, int port, const string &username, const string &password);

        // Destructor
        ~SMTP();

        // Public function to send email
        void sendmail(const string &from, const string &to, const string &subject, const string &body);
};

// Constructor
SMTP::SMTP(const string &server, int port, const string &username, const string &password) {
    // Initialize SSL library
    SSL_library_init();

    // Create new SSL context
    ctx = SSL_CTX_new(SSLv23_client_method());

    // Create new SSL connection
    bio = BIO_new_ssl_connect(ctx);

    // Get SSL object
    BIO_get_ssl(bio, &ssl);

    // Set SSL to automatically retry on failure
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    // Set hostname for SSL connection
    BIO_set_conn_hostname(bio, (server + ":" + to_string(port)).c_str());

    // Connect to server
    if(BIO_do_connect(bio) <= 0) {
        throw runtime_error("Error connecting to server");
    }

    // Send EHLO command and get response
    send("EHLO localhost\r\n");
    recv();

    // Start TLS
    send("STARTTLS\r\n");
    recv();
    SSL_set_tlsext_host_name(ssl, server.c_str());
    SSL_do_handshake(ssl);

    // Send EHLO again
    send("EHLO localhost\r\n");
    recv();

    // Authenticate
    send("AUTH LOGIN\r\n");
    recv();
    send(base64_encode(username) + "\r\n");
    recv();
    send(base64_encode(password) + "\r\n");
    recv();
}

// Destructor
SMTP::~SMTP() {
    // Send QUIT command
    send("QUIT\r\n");

    // Free SSL resources
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
}

// Function to send a command to the server and get the response
void SMTP::send(const string &str) {
    if(BIO_write(bio, str.c_str(), str.length()) <= 0