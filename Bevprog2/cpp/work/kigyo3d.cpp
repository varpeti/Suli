#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "algorithm"
#include "iostream"

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

struct Skoord
{	
	double x;
	double y;
	double z;

	Skoord(double cx,double cy,double cz)
	{
		x=cx;
		y=cy;
		z=cz;
	}

	Skoord()
	{
		x=0;
		y=0;
		z=0;
	}

	Skoord operator+(Skoord);
	Skoord operator-(Skoord);
	Skoord operator/(double);
	double operator|(Skoord);
};

Skoord Skoord::operator+(Skoord b)
{
	Skoord c;
	c.x = x+b.x;
	c.y = y+b.y;
	c.z = z+b.z;
	return(c);
}

Skoord Skoord::operator-(Skoord b)
{
	Skoord c;
	c.x = x-b.x;
	c.y = y-b.y;
	c.z = z-b.z;
	return(c);
}

Skoord Skoord::operator/(double b)
{
	Skoord c;
	c.x = x+x/b;
	c.y = x+y/b;
	c.z = x+z/b;
	return(c);
}

double Skoord::operator|(Skoord b)
{
	return sqrt( (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z) ); 
}


struct Sboxok
{
	private: 
	Skoord k; //Azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	unsigned char rr,gg,bb;
	Skoord f; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	bool tipus; // 0 fal 1 kaja;

	public:
	Sboxok (Skoord ek, int szin, bool etipus)
	{
		k=k+ek;
		tipus = etipus;
		
		if (szin<255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	}

	bool operator < (const Sboxok& str) const { return (f.z<str.f.z); } // Ez felel azért hogy a hátul lévőt elöbb rajzolja ki

	double supdate(Skoord c, double alpha, double ex, double ey);
	void srajzol();
	void getKoords(Skoord &c);

};

double Sboxok::supdate(Skoord c, double alpha, double ex, double ey) 
{
	if (!tipus) {
		Skoord a = c-k;
		double h = c|k; if (h==0) h=1; // normalizásás csak e = 3;
		cout << "h: " << h << endl;
		//k=a/h;
	}

	f=k;
	forgat(f.x,f.y,f.z,alpha);

	double ax = round(f.x + f.z/2 + kx/2);
	double ay = round(f.y + f.z/2 + ky/2);
	return (sqrt((ax-ex)*(ax-ex)+(ay-ey)*(ay-ey)));
}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját)
	int ax = round(f.x + f.z/2 + kx/2);
	int ay = round(f.y + f.z/2 + ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	stringstream str;
	str << int(k.x) << " " << int(k.y) << " " << int(k.z);
	string s = str.str();

	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(-(kz/2+f.z)/(kz/2)*10,-(kz/2+f.z)/(kz/2)*10) // a Z távolság függvényében változik a méret
		<< text(s);
}

void Sboxok::getKoords(Skoord &c)
{
	c=k;
}

void updatedraw(std::vector<Sboxok> &v, int &target,double alpha, double ex, double ey)
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
		Skoord c;
		if (i>0) v[i-1].getKoords(c); 
		else 
		{
			v[target].getKoords(c); // target irányába
			//v[i].getKoords(px,py,pz); // fej koordinátái
		}
		double t = v[i].supdate(c,alpha,ex,ey);
		if (t<mint) {mint=t;minid=i;}
		rajZ[i].srajzol(); //az új sorba rendezett vektor alapján rajzolok
	}

	if (minid>0) target=minid;

	Skoord k; v[target].getKoords(k);
	//cout << int(k.x) << " " << int(k.y) << " " << int(k.z) << endl;
	gout << refresh;

}

int main()
{
	std::vector<Sboxok> v;
	int szin = 0;

	srand (time(NULL));
	gout.open(kx,ky,teljes);

	gin.timer(20);

	Skoord n;
	Sboxok b(n,szin,false);
	szin++; if (szin>3*255) szin=0;
	v.push_back(b);

	double mertek = 0.01;
	double rpx = 0;
	double alpha = PI;

	double ex=0,ey=0;

	int kaja = 0;
	int target=1;
	
	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alpha+=rpx;
			updatedraw(v,target,alpha,ex,ey);
			while (kaja<mkaja)
			{
				Skoord n(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2);
				Sboxok b(n,szin,true);
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