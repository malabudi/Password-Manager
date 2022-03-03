#include <iostream>
#include "UserPasswordManager.h"

const std::string UserPasswordManager::upperAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string UserPasswordManager::lowerAlph = "abcdefghijklmnopqrstuvwxyz";
const std::string UserPasswordManager::digitStr = "0123456789";

int main()
{
    UserPasswordManager myPasswords;

    myPasswords.changePassword();

    return 0;
}
