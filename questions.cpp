//#include <iostream>
//#include <string>

//void questions() {
//    std::string question1 = "What was the name of your first pet? ";
//    std::string question2 = "What is your mother's maiden name? ";
//    std::string question3 = "What year was your father (or mother) born? ";
//    std::string answer;
//    int choice;

//    std::cout << "Please select a question:\n"
//              << "1. " << question1 << "\n"
//              << "2. " << question2 << "\n"
//              << "3. " << question3 << "\n";
//    std::cin >> choice;

//    switch (choice) {
//        case 1:
//            std::cout << question1;
//            break;
//        case 2:
//            std::cout << question2;
//            break;
//        case 3:
//            std::cout << question3;
//            break;
//        default:
//            std::cout << "Invalid choice.\n";
//    }

//    std::cin >> answer;
//    std::cout << "Your answer is " << answer << std::endl;

//}

//void checksecurity() {
//    std::string username;
//    std::string security_question;
//    std::string security_answer;
//    std::string password;

//    std::cout << "Username: ";
//    std::cin >> username;

//    std::cout << "Security question: ";
//    std::cin.ignore();
//    std::getline(std::cin, security_question);

//    std::cout << "Security answer: ";
//    std::getline(std::cin, security_answer);

//    // Check the username and security answer against the stored values.
//    // If they match, reset the password.
//    // If they do not match, return an error.

//    std::cout << "Your password has been reset.\n";
//    std::cout << "New password: ";
//    std::cin >> password;

//    // Store the new password for the user.
//};
