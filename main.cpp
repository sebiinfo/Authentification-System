
#include <iostream>
#include "mail.cpp"
#include "profile.hpp"

using namespace std;


int main(){

    int random_generated = generateRandomNumber();
    mail(random_generated, "sophieclaireantoun0@gmail.com");
    if (verification(random_generated)){
        std::cout<<"ok"<<std::endl;
//        Profile::change_password();
    }
        ;
    return 0;
}
