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
const int maxkaja = 20;
const int szindifferencial = 1;
const int hosszszorzo = 10;

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

struct SRekord
{	
	// playerstat
	int kaja;
	int pont;
	int hossz;
	int elet;
	double sebesseg;

	SRekord(int eelet, int esebesseg)
	{
		kaja=0;
		pont=0;
		hossz=1;
		elet=eelet*hosszszorzo;
		sebesseg=esebesseg;
	}
};

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

	void srajzol();
	Skoord getKoords();
	Skoord getSzin();

	// az update specifikus, kifejezetten a játékoz lett írva, nem kéne tagfüggvénynek lennie csak így kevesebbet kell gépelni :D
	double supdate(Skoord c, double alpha, double ex, double ey, Skoord fej, SRekord &rekord, int id);

};

double Sboxok::supdate(Skoord c, double alpha, double ex, double ey, Skoord fej, SRekord &rekord, int id)
{
	if (!tipus) {
		Skoord a = c-k; //vektor számolás
		double h = c|k; if (h==0) h=1; else h/=( (rand()%200)/100+rekord.sebesseg); //normalizálás || h/=3 miatt gyorsabban halad
		k=k+a/h; //mozgatás
	}
	f = k.forgat(alpha); // forgatás rajzoláshoz

	if (tipus) {
		if ((fej|k)<10) {
			tipus=false;
			if (rekord.hossz+hosszszorzo>id) rekord.pont+=((rand()%10+5)*rekord.sebesseg); else rekord.elet--;
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

	double mx = (kz/2+f.z)/(kz/2)*10; if (mx<3) mx=3; // a Z távolság függvényében változik a méret
	double my = (kz/2+f.z)/(kz/2)*10; if (my<3) my=3;
	gout << color(rr,gg,bb)
		<< move_to(ax,ay)
		<< box(mx,my);
		//<< text(s);
}

Skoord Sboxok::getKoords()
{
	return k;
}

Skoord Sboxok::getSzin()
{
	return Skoord(rr,gg,bb);
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

	// Target vonal
	Skoord targetbox = v[target].getKoords().forgat(alpha); // target koordinátái
	Skoord ffej = fej.forgat(alpha);
	gout << color(255,255,255)
			<< move_to(ffej.x + ffej.z/2 + kx/2 + (kz/2+ffej.z)/(kz/2)*5,ffej.y + ffej.z/2 + ky/2 +(kz/2+ffej.z)/(kz/2)*5 )
			<< line_to(targetbox.x + targetbox.z/2 + kx/2 + (kz/2+targetbox.z)/(kz/2)*5,targetbox.y + targetbox.z/2 + ky/2 + (kz/2+targetbox.z)/(kz/2)*5);
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

	Skoord rgb = v[rekord.hossz+hosszszorzo].getSzin();
	gout << color(rgb.x,rgb.y,rgb.z);
	for (int i = 0; i < int(rekord.elet/hosszszorzo); ++i)
	{
		gout << move_to(10+i*40,10) << box(25,25);
	}

	gout << refresh;

}

int main()
{
	srand (time(NULL));

	gout.open(kx,ky,teljes);

	gin.timer(20);

	std::vector<Sboxok> v;
	int szin = rand()%(3*255);

	Skoord n;
	for (int i = 0; i < hosszszorzo*3; ++i)
	{
		Sboxok b(n,szin,true); v.push_back(b);
		szin+=szindifferencial; if (szin>3*255) szin=0;
	}

	double mertek = 0.01;
	double rpx = 0;
	double alpha = PI;

	double ex=0,ey=0;

	int target=1;
	SRekord rekord(5,2);
	
	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alpha+=rpx; // forgatás
			updatedraw(v,target,alpha,ex,ey,rekord);
			while (rekord.kaja<maxkaja*hosszszorzo) // létrehozás
			{
				Skoord n(rand()%(9*kx/10)-(9*kx/20),rand()%(9*ky/10)-(9*ky/20),rand()%(9*kz/10)-(9*kz/20)); // azért legyenenek bentebb a pontok
				for (int i = 0; i < hosszszorzo; ++i)
				{
					Sboxok b(n,szin,true); v.push_back(b);
					szin+=szindifferencial; if (szin>3*255) szin=0;
				}
		
				rekord.kaja+=hosszszorzo;
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
	switch(sz) //Hmm ctrl+c ctrl+v a "kockás" játékból :D
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

void pontkiir(int pont)
{

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
