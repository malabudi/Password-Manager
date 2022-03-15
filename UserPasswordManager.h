#include <vector>
#include <iostream>

class UserPasswordManager
{
    private:
        bool isValidPassword;
        std::string currentPassword;
        std::vector<std::string> oldPasswords; // old passwords are unencrypted

        void createPassword();
        bool validatePassword(std::string password);
        std::string encryptPassword(std::string password);
        std::string decryptPassword();

    public:
        // static vars
        static const std::string upperAlph;
        static const std::string lowerAlph;
        static const std::string digitStr;

        UserPasswordManager();

        // methods
        void changePassword();
        bool verifyPassword(std::string passToVerify);
};
