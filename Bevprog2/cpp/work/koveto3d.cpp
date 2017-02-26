#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "algorithm"

#define PI 3.141592

using namespace genv;
using namespace std;

const int kx = 1900;
const int ky = 1060;
const int kz = round((kx+ky)/2);
const bool teljes = false;
int elemszam = 5; //*3*255


struct Sboxok
{
	double x; //és azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	double y;
	double z;
	unsigned char rr,gg,bb;
	double fx; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	double fy; 
	double fz; 

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

double px = PI; double rpx = 0.0;
double py = PI; double rpy = 0.0;
double pz = PI; double rpz = 0.0;

std::vector<Sboxok> v;
int szin = 0;

void Sboxok::supdate(double cx, double cy, double cz) 
{
	double a = cx-x;
	double b = cy-y;
	double c = cz-z;
	double h = sqrt(a*a+b*b+c*c)/(3); if (h==0) h=1; // normalizásás csak e = 3;
	x+=a/h;
	y+=b/h;
	z+=c/h;

	//y tengely körüli forgatás (2d-s forgatási mátrixból tippeltem a 3d-st)
	fx= x*cos(px)+z*sin(px);
	fz= -x*sin(px)+z*cos(px);

	//x tengely körüli forgatás
	fy= y*cos(py)-fz*sin(py);
	fz= y*sin(py)+fz*cos(py);

	/*/z tengely körüli forgatás //nem kell z-re mert zavaró
	fx= fx*cos(pz)-fy*sin(pz);
	fy= fy*sin(pz)+fx*cos(pz);*/

}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját)
	int ax = round(fx + fz/2) +floor(kx/2);
	int ay = round(fy + fz/2) +floor(ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	/*stringstream str;
	str << int(nx) << " " << int(ny) << " " << int(nz);
	string s = str.str();*/

	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(-(kz/2+fz)/(kz/2)*10,-(kz/2+fz)/(kz/2)*10); // a Z távolság függvényében változik a méret
}


bool sortZ (const Sboxok &a, const Sboxok &b) { return (a.fz<b.fz); } // Ez felel azért hogy a hátul lévőt elöbb rajzolja ki

void updatedraw()
{
	std::vector<Sboxok> rajZ = v; // új vektor
	std::sort(rajZ.begin(), rajZ.end(), sortZ); // sorba rendezés

	int id = 0;
	for (vector<Sboxok>::iterator i=v.begin(); i!=v.end();)
	{
		int sid=id;
		if (id<v.size()-1) id++; else id=0; 
		i->supdate(v[id].x,v[id].y,v[id].z);
		//i->srajzol();
		rajZ[sid].srajzol(); //az új sorba rendezett vektor alapján rajzolok
		i++;
	}

}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	//gout.showmouse(false); 
	//*
	for (int i = 0; i < (3*255*elemszam); ++i)
	{
		Sboxok b(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2,szin);
		szin++; if (szin>3*255) szin=0;
		v.push_back(b);
	}

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box(kx,ky);

			updatedraw();

			gout << refresh;
			py+=rpy;
			px+=rpx;
		}
		else if (ev.type==ev_key)
		{
			double mertek = 0.03;
			if (ev.keycode==key_up 		or ev.keycode=='w') rpy=mertek;
			if (ev.keycode==key_down 	or ev.keycode=='s') rpy=-mertek;
			if (ev.keycode==key_right 	or ev.keycode=='d') rpx=-mertek;
			if (ev.keycode==key_left 	or ev.keycode=='a') rpx=mertek;

			if (-ev.keycode==key_up 	or -ev.keycode=='w') rpy=0;
			if (-ev.keycode==key_down 	or -ev.keycode=='s') rpy=0;
			if (-ev.keycode==key_right 	or -ev.keycode=='d') rpx=0;
			if (-ev.keycode==key_left 	or -ev.keycode=='a') rpx=0;
		}
		else if (ev.type==ev_mouse)
		{
			if (ev.button==btn_right) for(Sboxok &i:v) if (rand()%30==3) {i.x=rand()%kx-kx/2;i.y=rand()%ky-ky/2;i.z=rand()%kz-kz/2;} //egy pár random pozícióba
			if (ev.button==btn_left) {v[0].x=rand()%kx-kx/2;v[0].y=rand()%ky-ky/2;v[0].z=rand()%kz-kz/2;} // az első random pozícióba
		}
	}
	return 0;
}