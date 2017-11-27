#include <iostream>
#include <string>

using namespace std; 

bool van_benne_p0(string str)
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {      
        if ( str.at(i)=='\0' ) return true;
    }
    return false;
}

void print(string str,string nev)
{
	cout << nev << ":\n\ttartalma: " << str << "\n\tvan benne \\0: " << van_benne_p0(str) << "\n\tmerete: " << str.size() << endl;
}

void egyenlo(string a, string b, string an, string bn)
{
	cout << "\t" << an << "==" << bn << ": " << (a==b) << endl; 
}


int main()
{	
	string a1="q",a2="qq";

	string alma = ""; // Jó módszer
	alma += a1 + '\0';
	alma += a2 + '\0';
	
	string korte = ""; //Rossz
	korte += a2 + '\0';
	korte += a1 + '\0';

	string banan = "q\0qq\0"; //Rossz

	string szilva = "q"; // Jó
	szilva.push_back('\0');
	szilva += "qq";
	szilva.push_back('\0');

	string kivi = ""; //Rossz
	kivi += "q" + '\0'; //azért mert a "q" az igazából char[] és nem string
	kivi += "qq" + '\0';

	//Adatok kiírása
	print(alma,"alma");
	print(korte,"korte");
	print(banan,"banan");
	print(szilva,"szilva");
	print(kivi,"kivi");

	//Egyenlőség teszt
	cout << endl << "Egyenloseg:\n" << endl;
	egyenlo(alma,korte,"alma","korte");
	egyenlo(alma,banan,"alma","banan");
	egyenlo(alma,szilva,"alma","szilva");
	egyenlo(alma,kivi,"alma","kivi");

	return 0;
}
