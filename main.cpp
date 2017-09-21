#include "Login.h"
#include "AccountManager.h"
#include <iostream>

using namespace std;

int main()
{
	//dummy main currently for testing purposes
    AccountManager user;
    cout<<user.decryptString(user.encryptString("hello"));
    return 0;
}
