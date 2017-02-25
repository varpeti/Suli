//CODEINGAME
#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 600;
const int kz = round((kx+ky)/2);
const bool teljes = false;

double alfa = 0.0;
int ex = 0;

struct Sboxok
{
	double x;
	double y;
	double z;
	unsigned char rr,gg,bb;

	Sboxok (double ex, double ey, double ez, int szin)
	{
		x = ex;
		y = ey;
		z = ez;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	void supdate(double cx, double cy, double cz);
	void srajzol();

};

void Sboxok::supdate(double cx, double cy, double cz) 
{
	double a = cx-x;
	double b = cy-y;
	double c = cz-z;
	double h = sqrt(a*a+b*b+c*c)/(3); if (h==0) h=1; // normalizásás csak e = 3;
	x+=a/h;
	y+=b/h;
	z+=c/h;

}

void Sboxok::srajzol()
{

	//y tengely körüli forgatás (2d-s forgatási mátrix csak y helyett z)
	double nx= x*cos(alfa)-z*sin(alfa);
	double ny= y;
	double nz= x*sin(alfa)+z*cos(alfa);

	//2d leképzés (Leggagyibb ami létezik, de legalább saját)
	int ax = round(nx + nz/2) +floor(kx/2);
	int ay = round(ny + nz/2) +floor(ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;


	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
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
		i->supdate(v[id].x,v[id].y,v[id].z);
		i->srajzol();
		i++;
	}
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	//gout.showmouse(false); 
	//*
	for (int i = 0; i < (3*255*3); ++i)
	{
		Sboxok b(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2,szin);
		szin++; if (szin>3*255) szin=0;
		v.push_back(b);
	}/*
	int fx = 0;
	int fy = 0;
	int m = 50;
	Sboxok b1(fx+m,fy+m,m,0); v.push_back(b1);
	Sboxok b2(fx-m,fy-m,m,0); v.push_back(b2);
	Sboxok b3(fx-m,fy+m,m,0); v.push_back(b3);
	Sboxok b4(fx+m,fy-m,m,0); v.push_back(b4);

	Sboxok b5(fx+m,fy+m,-m,200); v.push_back(b5);
	Sboxok b6(fx-m,fy-m,-m,200); v.push_back(b6);
	Sboxok b7(fx-m,fy+m,-m,200); v.push_back(b7);
	Sboxok b8(fx+m,fy-m,-m,200); v.push_back(b8); // */



	gin.timer(20);

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
		else if (ev.type==ev_mouse)
		{
			
			if (ex-ev.pos_x<0) alfa+=0.03; else alfa-=0.03; // forgatási szög
			ex=ev.pos_x;

			if (ev.button==btn_right) for(Sboxok &i:v) if (rand()%30==3) {i.x=rand()%kx-kx/2;i.y=rand()%ky-ky/2;i.z=rand()%kz-kz/2;} //egy pár random pozícióba

			if (ev.button==btn_left) {v[0].x=rand()%kx-kx/2;v[0].y=rand()%ky-ky/2;v[0].z=rand()%kz-kz/2;} // az első random pozícióba
		}
	}
	return 0;
}
