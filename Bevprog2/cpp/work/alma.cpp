#include "../graphics.hpp"
#include "sstream"
#include "stdlib.h"
#include "time.h"
#include "math.h"

using namespace genv;
using namespace std;

struct A
{
	int x,y;
	canvas T;
	A *next;
	A(int a, int b)
	{
		x = a;
		y = b;
		T.open(100,100);
	}
};

int main()
{
	srand (time(NULL));
	gout.open(400,400);

	A *kezdo;
	kezdo = new A(rand()%450,rand()%450);
	kezdo->next = NULL;

	A *vegzo;
	vegzo = kezdo;
	for (int i = 0; i < 1000; ++i)
	{
		vegzo->next = new A(rand()%350,rand()%350);
		vegzo = vegzo->next;
		vegzo->next = NULL;
	}


	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box_to(399,399);
		
		gout << color(255,255,255) 
			<< move_to(200,200) 
			<< line_to(ev.pos_x,ev.pos_y);

		stringstream str;
		str << ev.pos_x << " : " << ev.pos_y;
		string s = str.str();
		gout << move_to(20,20) 
			<< text(s);

		gout << move_to(22,22) << line(gout.twidth(s),0);

		A *it = kezdo;
		if ( it != NULL ) {
			while ( it->next != NULL)
			{
				gout << move_to(it->x,it->y)
					<< box(10,10);
				it = it->next;
			}
			A *d = kezdo->next->next;
			if (d) {
				kezdo->next->next = kezdo->next->next->next;
				delete d;
			}
			
		}

		gout << refresh;

	}
	return 0;
}
