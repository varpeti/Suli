#include <iostream>
#include <string>
#include <sstream>
#include "hash.hpp"

using namespace std; 

bool contain_p0(string str) // False ha tartalmaz \0-at
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {      
        if ( str.at(i)=='\0' ) return false;
    }
    return true;
}


int main()
{	string a1="q",a2="qq";
	string alma = "";
	alma += a1 + '\0'; // A alma += "q" + '\0' Nem működik!!!
	alma += a2 + '\0';
	string korte = "";
	korte += a2 + '\0';
	korte += a1 + '\0';


	cout << alma << " " << korte << endl;
	cout << contain_p0(alma) << " " << alma.size() << endl;
	cout << (alma==korte) << endl;
	HASH hash;
	hash.set(alma,0);
	cout << hash.get(alma) << endl;
	cout << hash.get(korte) << endl;

	getchar();
	
	return 0;
}
