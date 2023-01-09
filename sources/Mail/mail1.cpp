#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
CURL *curl;
CURLcode res;
string email = "systemauthentification@gmail.com"; // Replace with your email
string password = "sophieclairejasmine"; // Replace with your email password
string recipient = "sophieclaireantoun@gmail.com"; // Replace with recipient's email
string subject = "Email to Client"; // Replace with email subject
string body = "Hello, this is an email to my client."; // Replace with email body

curl = curl_easy_init();
if(curl)
{
cout <<"working"<< endl;
curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
curl_easy_setopt(curl, CURLOPT_MAIL_FROM, email.c_str());
struct curl_slist *recipients = NULL;
recipients = curl_slist_append(recipients, recipient.c_str());
curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
curl_easy_setopt(curl, CURLOPT_READDATA, NULL);
curl_easy_setopt(curl, CURLOPT_MAIL_FROM, email.c_str());
stringstream ss;
ss << "Subject: " << subject << "\r\n\r\n" << body << "\r\n";
string str = ss.str();
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
res = curl_easy_perform(curl);
if(res != CURLE_OK)
{
cout << "Error sending email: " << curl_easy_strerror(res) << endl;
}
else
{
cout << "Email sent successfully!" << endl;
}
curl_slist_free_all(recipients);
curl_easy_cleanup(curl);
}
return 0;
}