//CODEINGAME
#include "../graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 600;

struct Sboxok
{
	int x;
	int y;
	unsigned char rr,gg,bb;

	Sboxok (int ex, int ey, int szin)
	{
		x = ex;
		y = ey;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	void supdate(int cx, int cy);
	void srajzol();

};

void Sboxok::supdate(int cx, int cy) 
{
	int a = cx-x;
	int b = cy-y;
	int h = floor( (abs(a)+abs(b))/(rand()%10+3) ); if (h==0) h=1;
	x+=ceil(a/h);
	y+=ceil(b/h);


}

void Sboxok::srajzol()
{
	//if (x>=kx or x<0) return;
	//if (y>=ky or y<0) return;
	gout << color(rr,gg,bb)
		<< move_to(x,y)
		<< box(10,10);
}

std::vector<Sboxok> v;
int szin = 0;

void updatedraw()
{

	int id = 0;
	for (vector<Sboxok>::iterator i=v.begin(); i!=v.end();)
	{
		if (id<v.size()-1) id++; else id=0; 
		i->supdate(v[id].x,v[id].y);
		i->srajzol();
		i++;
	}
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,true);

	gout.showmouse(false); 

	for (int i = 0; i < (3*255*3); ++i)
	{
		Sboxok b(rand()%(kx-100)+50,rand()%(ky-100)+50,szin);
		szin++; if (szin>3*255) szin=0;
		v.push_back(b);
	}

	gin.timer(200);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box_to(1329,599);

			updatedraw();

			gout << refresh;
		}
		
	}
	return 0;
}
