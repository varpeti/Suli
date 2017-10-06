#include <iostream>
#include <exception>

#include <iostream>
#include "skiplist.hpp"

using namespace std;

int main() {
	
	SKIPLIST slist;

	slist.insert(10);
	slist.insert(11);
	slist.insert(13);
	slist.insert(17);

	if (slist.contains(13)) cout << "OK\n"; 		else cout << "Ajajj\n";
	if (slist.contains(15)) cout << "Ajajj\n"	; 	else cout << "OK\n";
	if (slist.contains(-3)) cout << "Ajajj\n"	; 	else cout << "OK\n";

	getchar();

	return 0;
}
