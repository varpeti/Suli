#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "time.h"
#include "math.h"
#include "algorithm"
#include "iostream"
#include "fstream"

#define PI 3.141592

using namespace genv;
using namespace std;

const int kx = 1330; // A játék émény ezen a felbontáson a legjobb.
const int ky = 700;
const int kz = round((kx+ky)/2);
const bool teljes = true; 			// Van teljes képernyős mód is. Laptopon jól szuperál.
const int nagyszam = kx+ky+kz;

struct Skoord // koordináták, szinek tárolására szolgáló struct, forgatással és 3d->2d leképzéssel
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
	Skoord lekepzes();
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

	//y tengely körüli forgatás
	se= f.x*cos(alpha)+f.z*sin(alpha);
	f.z= -f.x*sin(alpha)+f.z*cos(alpha);
	f.x= se;

	//x tengely körüli forgatás // Konstans pi, ha szükséges átírható változóra
	se= f.y*cos(PI)-f.z*sin(PI);
	f.z= f.y*sin(PI)+f.z*cos(PI);
	f.y= se;

	//z tengely körüli forgatás
	se= f.x*cos(PI)-f.y*sin(PI);
	f.y= f.x*sin(PI)+f.y*cos(PI);
	f.x= se;
	return f;
}

Skoord Skoord::lekepzes()
{
	double mz = (kz/2 + z)/(kz/2) *12; if (mz<3) mz=3; // Mekkora legyen | ne legyen kissebb 3x3-as nál
	return Skoord(x + z/2 + kx/2,y + z/2 + ky/2,mz); // a Z koordináta a nagyságát adja meg
}


struct Sboxok
{
	private: 
	Skoord k; //Azért tartom meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	Skoord szin; // Miért ne? ez is 3 :)
	Skoord f; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	Sboxok *kovet; // ki után menjen | NULL ha senki után | publikus lenne ha lehetne, de a SPECIFIKÁCIÓ szent :)

	public:
	Sboxok (Skoord ek, int gszin,Sboxok *ekovet)
	{
		k=k+ek;
		kovet = ekovet;
		
		if (gszin<=255) 				{szin.x=255-(gszin-0*255); 	szin.y=(gszin-0*255); 		szin.z=000;} 				else
		if (gszin>255 and gszin<=2*255) {szin.x=000; 				szin.y=255-(gszin-1*255); 	szin.z=(gszin-1*255);} 		else
		if (gszin>2*255) 				{szin.x=(gszin-2*255); 		szin.y=000; 				szin.z=255-(gszin-2*255);}
		//cout << "Letrejottem! " << this << endl;
	}

	~Sboxok ()
	{
		//cout << "Meghaltam! " << this << endl;
		// Kiirattam egy fileba a lértejövő és törlődő címeket és össszehasonlítottam a két filet. Minden amit létrehoztam meg is szünt miután kiléptem a menübe.
	}

	void supdate(double alpha,double sebesseg); // forgatás, mozgatás
	void srajzol(); // csak rajzolás
	Skoord getKoords(); //read only
	double getFZ(); // read only | sorba rendezéshez
	bool isSlpeep(); // read only
	void setKovet(Sboxok *ekovet); // write only
};

Skoord Sboxok::getKoords()
{
	return k;
}

double Sboxok::getFZ()
{
	return f.z;
}

bool Sboxok::isSlpeep()
{
	return not kovet;
}

void Sboxok::setKovet(Sboxok *ekovet)
{
	kovet=ekovet;
}

void Sboxok::supdate(double alpha,double sebesseg)
{	
	if (kovet) {
		Skoord c = kovet->getKoords();
		Skoord a = c-k; //vektor számolás 
		double h = c|k; if (h==0) h=1; //normalizálás
		k=k+a/(h/sebesseg); //mozgatás
	}

	f = k.forgat(alpha);
}

void Sboxok::srajzol()
{

	Skoord a = f.lekepzes();

	if (a.x>=kx-a.z or a.x<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (a.y>=ky-a.z or a.y<0) return;

	gout << color(szin.x,szin.y,szin.z)
		<< move_to(a.x,a.y)
		<< box(a.z,a.z);
}

int main()
{
	srand (time(NULL));

	gout.open(kx,ky,teljes);

	gout.load_font("font.ttf",40);

	gin.timer(20);

	ifstream be ("hs.dat");
	if (be.is_open()) {be >> maxpont; 

	event ev;

		while(gin >> ev and ev.keycode!=key_escape and rekord.elet>0 and rekord.pont<9999) // Játék ciklus
		{
			if (ev.type==ev_timer) 
			{
				alpha+=rpx; // forgatás
			
			}
			else if (ev.type==ev_key)
			{
				if (ev.keycode==key_right 	or ev.keycode=='d' or 	ev.keycode=='D') rpx=mertek; // Kamera forgatás
				if (ev.keycode==key_left 	or ev.keycode=='a' or 	ev.keycode=='A') rpx=-mertek;

				if (-ev.keycode==key_right 	or -ev.keycode=='d' or 	-ev.keycode=='D') rpx=0;
				if (-ev.keycode==key_left 	or -ev.keycode=='a' or 	-ev.keycode=='A') rpx=0;
			}
			else if (ev.type==ev_mouse)
			{
				eger.x=ev.pos_x;
				eger.y=ev.pos_y;
			}
		}

	}
	return 0;
}

