#include "AccountManager.h"

using namespace std;

AccountManager::AccountManager()
{
    //aes key to be set
    memset(aes_key, 'A', 256/8);
    AES_set_encrypt_key(aes_key, 256, &enc_key);
    AES_set_decrypt_key(aes_key, 256, &dec_key);
    if(firstTime())
    {
        RAND_bytes(iv, AES_BLOCK_SIZE);
        ofstream fout;
        fout.open("data.dat", ios_base::app);
        for(int i = 0; i<AES_BLOCK_SIZE;i++)
        {
            fout<<hex<<iv[i]<<" ";
        }
        fout<<endl;
        fout.close();
    }
    else
    {
        ifstream fin("data.dat");
        string temp;
        fin>>temp;
        for(int i = 0; i < AES_BLOCK_SIZE; i++)
        {
            fin>>hex>>iv[i];
        }
        while(readAccount(fin)){}
    }
}

bool AccountManager::firstTime()
{
    ifstream fin("data.dat");
    int lineCount = 0;
    string temp = "";
    while(fin>>temp)
    {
        lineCount++;
    }
    fin.close();
    if(lineCount == 1)
        return true;
    return false;
}

bool AccountManager::readAccount(ifstream &fin)
{
    string name;
    string username;
    string password;
    if(!(fin>>name))
        return false;
    fin>>username>>password;
    Account* newAccount = new Account(decryptString(name), decryptString(username), decryptString(password));
    accounts.push_back(*newAccount);
    return true;
}

void AccountManager::printAllAccounts()
{
    for(auto i: accounts)
    {
        cout<<i.returnName()<<endl;
    }
}

void AccountManager::addAccount(string name, string username, string password)
{
    ofstream fout;
    fout.open("data.dat", ios_base::app);
    fout<<encryptString(name)<<endl<<encryptString(username)<<endl<<encryptString(password)<<endl;
    fout.close();
}

void AccountManager::editAccount(int index, string name, string username, string password)
{
    ifstream fin("data.dat");
    string userPassword;
    string iv;
    fin>>userPassword>>iv;
    accounts[index].setName(name);
    accounts[index].setUserName(username);
    accounts[index].setPassword(password);
    fin.close();
    ofstream fout("data.dat");
    fout<<userPassword<<endl<<iv<<endl;
    for(auto i: accounts)
    {
        fout<<i.returnName()<<endl<<i.returnUserName()<<endl<<i.returnPassword()<<endl;
    }
    fout.close();
}

void AccountManager::viewAccount(int index)
{
    cout<<accounts[index].returnName()<<endl<<accounts[index].returnUserName()<<endl<<accounts[index].returnPassword()<<endl;
}

string AccountManager::encryptString(string stringInput)
{
    //convert string into unsigned char
    int size = stringInput.size();
    unsigned char input[size];
    strcpy((char*)input,stringInput.c_str());
    //create encryption buffer
    const int encLength = AES_BLOCK_SIZE;
    unsigned char output[encLength+1];
    memset(output,0,encLength);
    //setting iv_enc
    unsigned char iv_enc[AES_BLOCK_SIZE];
    memcpy(iv_enc, iv, AES_BLOCK_SIZE);
    //encrypt
    AES_cbc_encrypt(input, output, size, &enc_key, iv_enc, AES_ENCRYPT);
    stringstream ss;
    for(int i =0; i <encLength; i++)
    {
        ss<<output[i];
    }
    return ss.str();
}

string AccountManager::decryptString(string stringInput)
{
    int size = stringInput.size();
    unsigned char input[size];
    strcpy((char*)input,stringInput.c_str());
    //create decryption buffer, length unknown
    unsigned char output[256];
    memset(output,NULL,256);
    //setting iv_dec
    unsigned char iv_dec[AES_BLOCK_SIZE];
    memcpy(iv_dec, iv, AES_BLOCK_SIZE);
    //decrypt
    AES_cbc_encrypt(input, output, size, &dec_key, iv_dec, AES_DECRYPT);
    stringstream ss;
    int i = 0;
    while(output[i]!=NULL)
    {
        ss<<output[i];
        i++;
    }
    return ss.str();
}