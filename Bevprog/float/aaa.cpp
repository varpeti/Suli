#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;

int main()
{

	ofstream ki ("ki.csv");
	double a;
	a=0.8;
	for (double p = 2.8; p<4; p+=0.001)
		for (int i = 0; i < 50; ++i)
		{
			a=a*p*(1-a);
			ki << p  << ";" << i << ";" << a << ";" << endl;
		}

	ki.close();
	//getchar();
	return 0;
} 