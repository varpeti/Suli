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

const int kx = 1330;
const int ky = 600;
const int kz = round((kx+ky)/2);
const bool teljes = false;
const int mkaja = 10;


void forgat(double &fx,double &fy, double &fz,double alpha)
{
	double se;

	//y tengely körüli forgatás (2d-s forgatási mátrixból tippeltem a 3d-st)
	se= fx*cos(alpha)+fz*sin(alpha);
	fz= -fx*sin(alpha)+fz*cos(alpha);
	fx= se;

	//x tengely körüli forgatás
	se= fy*cos(PI)-fz*sin(PI);
	fz= fy*sin(PI)+fz*cos(PI);
	fy= se;

	//z tengely körüli forgatás
	se= fx*cos(PI)-fy*sin(PI);
	fy= fx*sin(PI)+fy*cos(PI);
	fx= se;
}


struct Sboxok
{
	private:
	double x; //és azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	double y;
	double z;
	unsigned char rr,gg,bb;
	double fx; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	double fy; 
	double fz; 
	bool tipus; // 0 fal 1 kaja;

	public:
	Sboxok (double ex, double ey, double ez, int szin, bool etipus)
	{
		x = ex;
		y = ey;
		z = ez;
		tipus = etipus;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	bool operator < (const Sboxok& str) const { return (fz<str.fz); } // Ez felel azért hogy a hátul lévőt elöbb rajzolja ki

	double supdate(double cx, double cy, double cz, double alpha, double ex, double ey, double px, double py, double pz);
	void srajzol();
	void getKoords(double &cx, double &cy, double &cz);

};

double Sboxok::supdate(double cx, double cy, double cz, double alpha, double ex, double ey, double hx, double hy, double hz) 
{
	if (!tipus) {
		double a = cx-x;
		double b = cy-y;
		double c = cz-z;
		double h = sqrt(a*a+b*b+c*c)/(1); if (h==0) h=1; // normalizásás csak e = 3;
		x+=a/h;
		y+=b/h;
		z+=c/h;
	}

	//if (sqrt((x-px)*(x-px)+(y-py)*(y-py)+(z-pz)*(z-pz))<5 and tipus) tipus=false;

	fx=x; fy=y; fz=z;
	forgat(fx,fy,fz,alpha);

	double ax = round(fx + fz/2 + kx/2);
	double ay = round(fy + fz/2 + ky/2);
	return (sqrt((ax-ex)*(ax-ex)+(ay-ey)*(ay-ey)));
}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját)
	int ax = round(fx + fz/2 + kx/2);
	int ay = round(fy + fz/2 + ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	stringstream str;
	str << int(x) << " " << int(y) << " " << int(z);
	string s = str.str();

	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(-(kz/2+fz)/(kz/2)*10,-(kz/2+fz)/(kz/2)*10) // a Z távolság függvényében változik a méret
		<< text(s);
}

void Sboxok::getKoords(double &cx, double &cy, double &cz)
{
	cx=x;
	cy=y;
	cz=z;
}


void updatedraw(std::vector<Sboxok> &v,double &px,double &py,double &pz, int &target,double alpha, double ex, double ey)
{
	gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box(kx,ky);


	std::vector<Sboxok> rajZ = v; // új vektor
	std::sort(rajZ.begin(), rajZ.end()); // sorba rendezés

	int minid = -1;
	double mint = 99999;

	for (int i = 0; i < v.size(); ++i)
	{ 
		double cx,cy,cz = 0;
		if (i>0) v[i-1].getKoords(cx,cy,cz); 
		else 
		{
			v[target].getKoords(cx,cy,cz); // target irányába
			v[i].getKoords(px,py,pz); // fej koordinátái
		}
		double t = v[i].supdate(cx,cy,cz,alpha,ex,ey,px,py,pz);
		if (t<mint) {mint=t;minid=i;}
		rajZ[i].srajzol(); //az új sorba rendezett vektor alapján rajzolok
	}
	if (minid>0) target=minid;

	gout << refresh;

}

int main()
{
	std::vector<Sboxok> v;
	int szin = 0;

	srand (time(NULL));
	gout.open(kx,ky,teljes);

	gin.timer(20);

	
	Sboxok b(0,0,0,szin,false);
	szin++; if (szin>3*255) szin=0;
	v.push_back(b);

	double px=0,py=0,pz=0; //fej
	int target=1;
	
	double mertek = 0.01;
	double rpx = 0;
	double alpha = PI;

	double ex=0,ey=0;

	int kaja = 0;
	
	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alpha+=rpx;
			if (px>kx/2 or px<-kx/2) break;
			if (py>ky/2 or py<-ky/2) break;
			if (pz>kz/2 or pz<-kz/2) break;
			updatedraw(v,px,py,pz,target,alpha,ex,ey);
			while (kaja<mkaja)
			{
				Sboxok b(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2,szin,true);
				szin+=5; if (szin>3*255) szin=0;
				v.push_back(b);
				kaja++;
			}
		}
		else if (ev.type==ev_key)
		{
			if (ev.keycode==key_right 	or ev.keycode=='d') rpx=mertek;
			if (ev.keycode==key_left 	or ev.keycode=='a') rpx=-mertek;

			if (-ev.keycode==key_right 	or -ev.keycode=='d') rpx=0;
			if (-ev.keycode==key_left 	or -ev.keycode=='a') rpx=0;
		}
		else if (ev.type==ev_mouse)
		{
			ex=ev.pos_x;
			ey=ev.pos_y;
		}
	}
	return 0;
}