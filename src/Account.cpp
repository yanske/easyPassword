#include "Account.h"
#include <string>
using namespace std;

Account::Account()
{
    accountName = "";
    accountUserName = "";
    accountPassword = "";
}
Account::Account(string name, string username, string password)
{
    accountName = name;
    accountUserName = username;
    accountPassword = password;
}
void Account::setName(string name)
{
    accountName = name;
}
void Account::setUserName(string username)
{
    accountUserName = username;
}
void Account::setPassword(string password)
{
    accountPassword = password;
}
string Account::returnName() const
{
    return accountName;
}
string Account::returnUserName() const
{
    return accountUserName;
}
string Account::returnPassword() const
{
    return accountPassword;
}
