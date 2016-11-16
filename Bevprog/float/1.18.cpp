#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "string"
#include "iomanip"

using namespace std;

int egyezik(char a, char b)
{
	return a==b;
}


int main()
{
	string s1,s2;
	cin >> s1 >> s2;
	if ( s1.length()>4 and s1.length()>4 and egyezik(s1.at(0),s2.at(0)) and egyezik(s1.at(1),s2.at(1)) and egyezik(s1.at(2),s2.at(2)) and egyezik(s1.at(3),s2.at(3)) and egyezik(s1.at(4),s2.at(4)) )
		cout << "igaz"; else cout << "hamis";
	//getchar();getchar(); //nem volt kedvem ciklust írni :p
} 