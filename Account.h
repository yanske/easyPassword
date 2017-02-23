#include <string>
using namespace std;
class Account
{
private:
    string accountName;
    string accountUserName;
    string accountPassword;
public:
    Account()
    {
        accountName = "";
        accountUserName = "";
        accountPassword = "";
    }
    Account(string name, string username, string password)
    {
        accountName = name;
        accountUserName = username;
        accountPassword = password;
    }
    void setName(string name)
    {
        accountName = name;
    }
    void setUserName(string username)
    {
        accountUserName = username;
    }
    void setPassword(string password)
    {
        accountPassword = password;
    }
    string returnName() const
    {
        return accountName;
    }
    string returnUserName() const
    {
        return accountUserName;
    }
    string returnPassword() const
    {
        return accountPassword;
    }
};
