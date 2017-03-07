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
const int ky = 700;
const int kz = round((kx+ky)/2);
const bool teljes = false;
const int nagyszam = kx+ky+kz+1; // A legnagyobb tav

struct SRekord
{	
	// playerstat
	int kaja;
	int pont;
	int hossz;

	// gamestat
	int maxkaja;
	int szindifferencial;
	int hosszszorzo;

	SRekord(int nehezseg) // Nehéz (3-30)
	{
		kaja=0;
		pont=500;
		hossz=1;

		maxkaja = nehezseg;
		szindifferencial = 2;
		hosszszorzo = 10;
	}
};

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

	Skoord forgat(double alpha);
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
	c.x = x/b;
	c.y = y/b;
	c.z = z/b;
	return(c);
}

double Skoord::operator|(Skoord b)
{
	return sqrt( (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z) );
}

Skoord Skoord::forgat(double alpha)
{
	double se;
	Skoord f=*this;

	//y tengely körüli forgatás (2d-s forgatási mátrixból tippeltem a 3d-st)
	se= f.x*cos(alpha)+f.z*sin(alpha);
	f.z= -f.x*sin(alpha)+f.z*cos(alpha);
	f.x= se;

	//x tengely körüli forgatás 
	se= f.y*cos(PI)-f.z*sin(PI);
	f.z= f.y*sin(PI)+f.z*cos(PI);
	f.y= se;

	//z tengely körüli forgatás
	se= f.x*cos(PI)-f.y*sin(PI);
	f.y= f.x*sin(PI)+f.y*cos(PI);
	f.x= se;
	return f;
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

	double supdate(Skoord c, double alpha, double ex, double ey, Skoord fej, SRekord &rekord, int id);
	void srajzol();
	Skoord getKoords();

};

double Sboxok::supdate(Skoord c, double alpha, double ex, double ey, Skoord fej, SRekord &rekord, int id)
{
	if (!tipus) {
		Skoord a = c-k; //vektor számolás
		double h = c|k; if (h==0) h=1; else h/=(rand()%300)/100+1; //normalizálás || h/=3 miatt gyorsabban halad
		k=k+a/h; //mozgatás
	}
	f = k.forgat(alpha); // forgatás rajzoláshoz

	if (tipus) {
		if ((fej|k)<10) {
			tipus=false;
			if (rekord.hossz+rekord.hosszszorzo>id) rekord.pont+=rand()%10+5; else rekord.pont-=rand()%10+6;
			rekord.hossz++;
			rekord.kaja--;
			
		} // Megette


		double ax = round(f.x + f.z/2 + kx/2); // Az egérhez legközelebbi kiválasztáshoz
		double ay = round(f.y + f.z/2 + ky/2);
		return (sqrt((ax-ex)*(ax-ex)+(ay-ey)*(ay-ey)));
	}

	return nagyszam;

}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját :D )
	int ax = round(f.x + f.z/2 + kx/2); 
	int ay = round(f.y + f.z/2 + ky/2);
	if (ax==kx/2 and ay==ky/2) return; // Az új objektum ne villanjon fel

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	/*stringstream str;
	str << int(k.x) << " " << int(k.y) << " " << int(k.z);
	string s = str.str(); //*/

	double mx = (kz/2+f.z)/(kz/2)*10; if (mx<1) mx=2; // a Z távolság függvényében változik a méret
	double my = (kz/2+f.z)/(kz/2)*10; if (my<1) my=2;
	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(mx,my);
		//<< text(s);
}

Skoord Sboxok::getKoords()
{
	return k;
}

void pontkiir(int pont);

void updatedraw(std::vector<Sboxok> &v, int &target,double alpha, double ex, double ey,SRekord &rekord)
{
	gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box(kx,ky);

	gout << color(25,25,25);
	pontkiir(rekord.pont);


	std::vector<Sboxok> rajZ = v; // új vektor a sorba rajzoláshoz
	std::sort(rajZ.begin(), rajZ.end()); // sorba rendezés

	int minid = -1; // Az egérhez leközelebbi // minimum kiválasztás
	double mint = nagyszam;

	Skoord fej = v[0].getKoords(); // fej koordinátái

	for (int i = 0; i < v.size(); ++i)
	{ 
		Skoord c;
		if (i>0) c=v[i-1].getKoords(); // a kígyó irányába
		else c=v[target].getKoords(); // target irányába
		double t = v[i].supdate(c,alpha,ex,ey,fej,rekord,i);
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

	Skoord n;
	Sboxok b(n,szin,false);
	szin++; if (szin>3*255) szin=0;
	v.push_back(b);

	double mertek = 0.01;
	double rpx = 0;
	double alpha = PI;

	double ex=0,ey=0;

	int target=1;
	SRekord rekord(10);
	
	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alpha+=rpx;
			updatedraw(v,target,alpha,ex,ey,rekord);
			while (rekord.kaja<rekord.maxkaja*rekord.hosszszorzo)
			{
				Skoord n(rand()%(9*kx/10)-(9*kx/20),rand()%(9*ky/10)-(9*ky/20),rand()%(9*kz/10)-(9*kz/20)); // azért legyenenek bentebb a pontok
				for (int i = 0; i < rekord.hosszszorzo; ++i)
				{
					Sboxok b(n,szin,true); v.push_back(b);
					szin+=rekord.szindifferencial; if (szin>3*255) szin=0;
				}
		
				rekord.kaja+=rekord.hosszszorzo;
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

void pontkirajz(int x, int y, int sz)
{
	switch(sz)
	{
		case 0: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 1: gout << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 2: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30); break;
		case 3: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30); break;
		case 4: gout << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 5: gout << move_to(x+30,y) << box(90,30) << move_to(x,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30); break;
		case 6: gout << move_to(x+30,y) << box(90,30) << move_to(x,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30) << move_to(x,y+30+90+30) << box(30,90); break;
		case 7: gout << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y) << box(90,30); break;
		case 8: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30) << move_to(x,y+30+90+30) << box(30,90); break;
		case 9: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30); break;
	}
}

int gpont;

void pontkiir(int pont)
{
	if (gpont!=pont) cout << "d pont: " << pont-gpont << endl;
	gpont=pont;

	int seged, s2;
	s2=pont;

	seged = s2/10000;
	s2=s2-10000*seged;
	pontkirajz(kx/2-2*160-75,ky/2-135,seged);

	seged = s2/1000;
	s2=s2-1000*seged;
	pontkirajz(kx/2-1*160-75,ky/2-135,seged);

	seged = s2/100;
	s2=s2-100*seged;
	pontkirajz(kx/2-0*160-75,ky/2-135,seged);

	seged = s2/10;
	s2=s2-10*seged;
	pontkirajz(kx/2+1*160-75,ky/2-135,seged);

	seged = s2;
	pontkirajz(kx/2+2*160-75,ky/2-135,seged);
}
