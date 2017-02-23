#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <openssl/sha.h>

#define SHA256Length 256

using namespace std;

class Login
{
private:
    string salt;
    unsigned int errorCounter;
    string password;

public:
    Login(string newSalt = "SaltySalt")
    {
        salt = newSalt;
        errorCounter = 0;
        ifstream fin("data.dat");
        if(!fin.good())
        {
            bool passwordSet = false;
            while(!passwordSet)
            {
                string tempPassword;
                ofstream fout("data.dat");
                cout << "New password: ";
                cin >> tempPassword;
                fout << returnHash(tempPassword)<<endl;
                passwordSet = true;
                fout.close();
            }
        }
        fin >> password;
    }

    void sha256(const string str, unsigned char hash[])
    {
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, str.c_str(), str.size());
        SHA256_Final(hash, &sha256);
    }

    string hexHash(unsigned char pass[], unsigned char salt[])
    {
        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex <<setw(2) << setfill('0') << (int)pass[i] + (int)salt[i];
        }
        return ss.str();
    }

    string returnHash(const string str)
    {
        unsigned char passHash[SHA256Length];
        unsigned char saltHash[SHA256Length];
        sha256(str, passHash);
        sha256(salt, saltHash);
        return hexHash(passHash,saltHash);
    }

    bool loginRequest()
    {
        while(errorCounter != 3)
        {
            string input;
            cout << "Password: ";
            cin >> input;
            if (returnHash(input) == password)
            {
                system("cls");
                cout << "Logged in!";
                return true;
            }
            else
            {
                errorCounter++;
                system("cls");
                cout << "Error!" << endl;
            }
        }
        return false;
    }
};

