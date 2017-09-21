#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account
{
private:
    string accountName;
    string accountUserName;
    string accountPassword;
public:
    Account();
    Account(string name, string username, string password);
    void setName(string name);
    void setUserName(string username);
    void setPassword(string password);
    string returnName() const;
    string returnUserName() const;
    string returnPassword() const;
};

#endif