#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include <unistd.h>

using namespace std;

typedef struct s_alma s_alma;
typedef struct s_korte s_korte;

struct s_alma
{
	int ertek;
	struct s_korte *korte;
}alma;


struct s_korte
{
	int ertek;
	struct s_alma *alma;
}korte;


int main()
{
	korte.ertek = 10;
	alma.ertek = 9;
	korte.alma = &alma;
	alma.korte = &korte;
	cout << korte.alma->korte->alma->korte->alma->korte->ertek << endl;
	sleep(2);
	cout << korte.alma->korte->alma->korte->alma->ertek  << endl;
	cout << alma.korte->alma->korte->ertek;
	getchar();
} 