
#include <iostream>
#include "mail.cpp"
#include "profile.hpp"

using namespace std;


int main(){

    int random_generated = generateRandomNumber();
    mail(random_generated);
    if (verification(random_generated)){
        Profile::change_password();
    }
        ;
    return 0;
}
