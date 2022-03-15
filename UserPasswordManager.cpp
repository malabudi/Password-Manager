#include "UserPasswordManager.h"
#include <string>
#include <cctype>
#include <sstream>

// Private
void UserPasswordManager::createPassword()
{
    std::string password;

    std::cout << "\nPlease make sure your password: ";
    std::cout << "\n\tContains at least 8 characters";
    std::cout << "\n\tContains at least one lowercase letter";
    std::cout << "\n\tContains at least one uppercase letter";
    std::cout << "\n\tContains at least one digit";
    std::cout << "\n\tContains one of the following special characters:";
    std::cout << "\n\t! @ # $ % ~ ^ & * ( ) _ + = - ` < > ? : \" | \\ [ ] { }";
    std::cout << "\nEnter your password: ";
    std::getline(std::cin, password);

    this->isValidPassword = this->validatePassword(password);

    if (this->isValidPassword)
        this->currentPassword = this->encryptPassword(password);
}

bool UserPasswordManager::validatePassword(std::string password)
{
    bool lowercaseChars, uppercaseChars, digits, specialChars;
    int passSize = password.size();

    // brute force validation
    if (passSize < 8)
        return false;

    for (int i = 0; i < passSize; ++i)
    {
        if (isupper(password[i]))
            uppercaseChars = true;
        else if (islower(password[i]))
            lowercaseChars = true;
        else if (isdigit(password[i]))
            digits = true;
        else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '~' ||
                 password[i] == '^' || password[i] == '&' || password[i] == '*' || password[i] == '(' || password[i] == ')' || password[i] == '_' ||
                 password[i] == '+' || password[i] == '=' || password[i] == '-' || password[i] == '`' || password[i] == '<' || password[i] == '>' ||
                 password[i] == '?' || password[i] == ':' || password[i] == '"' || password[i] == '|' || password[i] == '\\' || password[i] == '[' ||
                 password[i] == ']' || password[i] == '{' || password[i] == '}')
            specialChars = true;
        else
            return false;
    }

    // check if password used
    for (std::string aPassword : this->oldPasswords)
    {
        if (password.compare(aPassword) == 0)
            return false;
    }

    return uppercaseChars && lowercaseChars && digits && specialChars;
}

std::string UserPasswordManager::encryptPassword(std::string password)
{
    std::string encryptedPass = "";
    int upperSubToken = 0, lowerSubToken = 0, digitSubToken = 0;
    int passSize = password.size();

    for (int i = 0; i < passSize; ++i)
    {
        if (isupper(password[i]))
            upperSubToken += password[i];
        else if (islower(password[i]))
            lowerSubToken += password[i];
        else if (isdigit(password[i]))
            digitSubToken += password[i];
    }

    upperSubToken = (upperSubToken % (26 - 1 + 1)) + 1;
    lowerSubToken = (lowerSubToken % (26 - 1 + 1)) + 1;
    digitSubToken = digitSubToken % 10;

    // add token to encrypted password
    if (upperSubToken < 9)
        encryptedPass += ("0" + std::to_string(upperSubToken));
    else
        encryptedPass += (std::to_string(upperSubToken));

    if (lowerSubToken < 9)
        encryptedPass += ("0" + std::to_string(lowerSubToken));
    else
        encryptedPass += (std::to_string(lowerSubToken));
    encryptedPass += std::to_string(digitSubToken);


    for (int i = 0; i < passSize; ++i)
    {
        if (isupper(password[i]))
            encryptedPass += this->upperAlph[((password[i] - 'A') + upperSubToken) % 26];
        else if (islower(password[i]))
            encryptedPass += this->lowerAlph[((password[i] - 'a') + lowerSubToken) % 26];
        else if (isdigit(password[i]))
            encryptedPass += this->digitStr[((password[i] - '0') + digitSubToken) % 10];
        else
            encryptedPass += password[i];
    }

    return encryptedPass;
}

std::string UserPasswordManager::decryptPassword()
{
    std::string decryptedPass;
    std::string encryptPassword = this->currentPassword;
    std::string password = encryptPassword.substr(5);
    int upperSubToken, lowerSubToken, digitSubToken;

    // Use stringstream to convert the tokens in encrypted password to ints
    std::stringstream ss1, ss2, ss3;

    ss1 << encryptPassword.substr(0, 2);
    ss1 >> upperSubToken;

    ss2 << encryptPassword.substr(2, 2);
    ss2 >> lowerSubToken;

    ss3 << encryptPassword.substr(4, 1);
    ss3 >> digitSubToken;

    for (int i = 0; i < password.size(); ++i)
    {
        if (isupper(password[i]))
            decryptedPass += this->upperAlph[((password[i] - 'A') + (26 - upperSubToken)) % 26];
        else if (islower(password[i]))
            decryptedPass += this->lowerAlph[((password[i] - 'a') + (26 - lowerSubToken)) % 26];
        else if (isdigit(password[i]))
            decryptedPass += this->digitStr[((password[i] - '0')  + (10 - digitSubToken)) % 10];
        else
            decryptedPass += password[i];
    }

    return decryptedPass;
}


// Public
UserPasswordManager::UserPasswordManager()
{
    this->createPassword();
    this->isValidPassword ? std::cout << "\nPassword created" : std::cout << "\nPassword could not be created";
}

void UserPasswordManager::changePassword()
{
    std::string newPassword;

    std::cout << "\nPlease make sure your password: ";
    std::cout << "\n\tContains at least 8 characters";
    std::cout << "\n\tContains at least one lowercase letter";
    std::cout << "\n\tContains at least one uppercase letter";
    std::cout << "\n\tContains at least one digit";
    std::cout << "\n\tContains one of the following special characters:";
    std::cout << "\n\t! @ # $ % ~ ^ & * ( ) _ + = - ` < > ? : \" | \\ [ ] { }";
    std::cout << "\nEnter your new password: ";
    std::getline(std::cin, newPassword);

    this->isValidPassword = this->validatePassword(newPassword);

    if (this->isValidPassword)
    {
        this->oldPasswords.push_back(this->currentPassword);
        this->currentPassword = this->encryptPassword(newPassword);
        std::cout << "\nPassword was successfully changed";
    }
    else
        std::cout << "\nPassword was not changed";
}

bool UserPasswordManager::verifyPassword(std::string passToVerify)
{
    std::string decryptedPass = this->decryptPassword();

    if (passToVerify.compare(decryptedPass) == 0)
        return true;

    return false;
}
