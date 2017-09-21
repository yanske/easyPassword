#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "Account.h"

using namespace std;

class AccountManager
{
    vector<Account> accounts;
    unsigned char aes_key[256/8];
    unsigned char iv[AES_BLOCK_SIZE];
    AES_KEY enc_key;
    AES_KEY dec_key;

public:
    AccountManager();
    bool firstTime();
    bool readAccount(ifstream &fin);
    void printAllAccounts();
    void addAccount(string name, string username, string password);
    void editAccount(int index, string name, string username, string password);
    void viewAccount(int index);
    string encryptString(string stringInput);
    string decryptString(string stringInput);
};

#endif