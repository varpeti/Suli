#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <iostream> // TODO: kivenni
#include "exp.hpp"

using namespace std;

class HASH
{
private:
    string htable[256];
    unsigned char _set(string &str);
public:
    HASH();
    //~HASH();
    void set(string str); // Belerak
    bool get(string str); // Benne van-e?
    void test(); //TODO: törlés
};

HASH::HASH()
{
    for (int i = 0; i < 256; ++i)
    {
        htable[i]="";
    }
}

unsigned char HASH::_set(string &str)
{
    unsigned int c = 1;
    for (int i = 0; i < str.size(); ++i)
    {
        c = (c*256+(unsigned char)str.at(i));
    }
    return c%257%256;
}

void HASH::set(string str)
{
    unsigned int it=0;
    unsigned char hid; 
    do {
        string u = str;
        u+=(unsigned char)it;
        hid = _set(u);
        it++;
    } while(htable[hid]!="" and htable[hid]!=str and it<256);

    if (it==256) {throw EXP("HASH_betelt"); }

    //cout << str << " " << it << " " << (int)hid << endl;
    htable[hid]=str;
}

bool HASH::get(string str)
{
    unsigned int it=0;
    unsigned char hid; 
    do {
        string u = str;
        u+=(unsigned char)it;
        hid = _set(u);
        it++;
    } while(htable[hid]!=str and htable[hid]!="" and it<256);

    //cout << it << endl;
    if (htable[hid]!=str) return false;
    return true;
}

void HASH::test()
{
    string str = " ";
    for (int i = 0; i < 32; ++i) //Átfordulás
    {
        string u = str;
        u+=(unsigned char)i;
        htable[_set(u)]="-";
    }
    for (int i = 0; i < 256; ++i)
    {
        if (htable[i]=="-") cout << i << endl;
    }
}

#endif