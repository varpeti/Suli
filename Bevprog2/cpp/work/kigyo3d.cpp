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
	//private: 
	Skoord k; //Azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	Skoord szin; // Miért ne? ez is 3 :)
	Skoord f; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	Sboxok *kovet;

	public:
	Sboxok (Skoord ek, int gszin,Sboxok *ekovet)
	{
		k=k+ek;
		kovet = ekovet;
		
		if (gszin<255) 					{szin.x=255-(gszin-0*255); 	szin.y=(gszin-0*255); 		szin.z=000;} 				else
		if (gszin>255 and gszin<2*255) 	{szin.x=000; 				szin.y=255-(gszin-1*255); 	szin.z=(gszin-1*255);} 		else
		if (gszin>2*255) 				{szin.x=(gszin-2*255); 		szin.y=000; 				szin.z=255-(gszin-2*255);}
	}

	~Sboxok ()
	{
		cout << "Meghaltam! " << this << endl;
	}

	bool operator < (const Sboxok& str) const { return (f.z<str.f.z); } // Ez felel azért hogy a hátul lévőt elöbb rajzolja ki

	void supdate(double alfa); // forgatás
	void srajzol();
	Skoord getKoords();
	Skoord getSzin();
};

Skoord Sboxok::getKoords()
{
	return k;
}

Skoord Sboxok::getSzin()
{
	return szin;
}

void Sboxok::supdate(double alpha)
{	
	if (kovet) {
		Skoord c = kovet->getKoords();
		Skoord a = c-k; //vektor számolás 
		double h = c|k; if (h==0) h=1; //normalizálás
		k=k+a/h; //mozgatás
	}

	f = k.forgat(alpha);
}

void Sboxok::srajzol()
{

	//2d leképzés (Leggagyibb ami létezik, de legalább saját :D )
	int ax = round(f.x + f.z/2 + kx/2); 
	int ay = round(f.y + f.z/2 + ky/2);

	if (ax>=kx-10 or ax<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (ay>=ky-10 or ay<0) return;

	stringstream str;
	str << int(k.x) << " " << int(k.y) << " " << int(k.z);
	string s = str.str(); //*/

	double mx = (kz/2+f.z)/(kz/2)*10; if (mx<3) mx=3; // a Z távolság függvényében változik a méret
	double my = (kz/2+f.z)/(kz/2)*10; if (my<3) my=3;
	gout << color(szin.x,szin.y,szin.z)
		<< move_to(ax,ay)
		<< box(mx,my)
		<< text(s);
}

void pontkiir(int pont);

double updategame()
{
	return 0.1;
}

void updatedraw(vector<Sboxok*> &boxok,double alfa,Skoord eger)
{
	gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box(kx,ky);

	gout << color(25,25,25);
	//pontkiir(100);

	for (int i = 0; i < boxok.size();i++)
	{
		boxok[i]->supdate(alfa);
		boxok[i]->srajzol();
		if ((boxok[i]->getKoords()|boxok[0]->getKoords())<50 and boxok[i]!=boxok[0]) 
		{
			delete boxok[i];
			boxok[i] = boxok[boxok.size()-1];
			boxok.pop_back();
		}
	}
	

	gout << refresh;

}

int main()
{
	srand (time(NULL));

	gout.open(kx,ky,teljes);

	gin.timer(20);

	double alfa 		= 0;
	double rpx			= 0;
	const double mertek = 0.03;

	double ex			= 0;
	double ey 			= 0;

	vector<Sboxok*> boxok;

	Sboxok *fej 		= new Sboxok(Skoord(0,0,0),0,NULL);
	boxok.push_back(fej);

	for (int i = 0; i < 10; ++i)
	{
		Sboxok *box = new Sboxok(Skoord(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2),0,fej);
		boxok.push_back(box);
	}
	


	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alfa+=rpx; // forgatás
			updatedraw(boxok,alfa,Skoord(ex-kx/2,ey-ky/2,0));
		
		}
		else if (ev.type==ev_key)
		{
			if (ev.keycode==key_right 	or ev.keycode=='d') rpx=mertek;
			if (ev.keycode==key_left 	or ev.keycode=='a') rpx=-mertek;

			if (-ev.keycode==key_right 	or -ev.keycode=='d') rpx=0;
			if (-ev.keycode==key_left 	or -ev.keycode=='a') rpx=0;
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
