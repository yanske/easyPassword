#ifndef LOGIN_H
#define LOGIN_H
#include <string>

class Login
{
private:
    string salt;
    unsigned int errorCounter;
    string password;

public:
    Login(string newSalt = "SaltySalt");

    void sha256(const string str, unsigned char hash[]);

    std::string hexHash(unsigned char pass[], unsigned char salt[]);

    std::string returnHash(const string str);

    bool loginRequest();
};

#endif