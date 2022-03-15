#include <iostream>
#include "UserPasswordManager.h"

const std::string UserPasswordManager::upperAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string UserPasswordManager::lowerAlph = "abcdefghijklmnopqrstuvwxyz";
const std::string UserPasswordManager::digitStr = "0123456789";

// Function prototypes
bool isValidMenuDecis(char& choice);

int main()
{
    int passChoice;
    char menuChoice;
    std::string passToVerify;
    bool isValidPass;

    std::cout << "\nWelcome to the password manager program";
    UserPasswordManager myPasswords;

    while (menuChoice != 'N')
    {
        std::cout << "\n\nPlease select from the menu below:";
        std::cout << "\n1. Change password";
        std::cout << "\n2. Verify password\n";
        std::cin >> passChoice;

        while (passChoice > 2 || passChoice < 1)
        {
            std::cout << "\nInvalid choice, please select the number from the menu below:";
            std::cout << "\n1. Change password";
            std::cout << "\n2. Verify password\n";
            std::cin >> passChoice;
        }

        std::cin.ignore(100, '\n');

        switch (passChoice)
        {
            case 1:
                myPasswords.changePassword();
                break;
            case 2:
                std::cout << "\nPlease enter your password to verify: ";
                std::getline(std::cin, passToVerify);

                isValidPass = myPasswords.verifyPassword(passToVerify);

                isValidPass ? std::cout << "\nYou entered the correct password" : std::cout << "\nThe password entered is invalid";
                break;
        }

        std::cout << "\nWould you like to continue the program? (Y/N)\n";
        std::cin >> menuChoice;

        while (isValidMenuDecis(menuChoice) == false)
        {
            std::cout << "\nInvalid input, please enter a valid choice";
            std::cout << "\nWould you like to continue the program? (Y/N)\n";
            std::cin >> menuChoice;
        }
    }


    return 0;
}

bool isValidMenuDecis(char& choice)
{
    if (choice >= 97 && choice <= 122)
        choice -= 32;

    if (choice == 'Y' || choice == 'N')
        return true;

    return false;
}
