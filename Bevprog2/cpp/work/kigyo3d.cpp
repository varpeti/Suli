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
const int nagyszam = kx+ky+kz;

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

Skoord Skoord::lekepzes()
{
	double mz = (kz/2 + z)/(kz/2) *10; if (mz<3) mz=3; // Mekkora legyen | ne legyen kissebb 3x3-as nál
	return Skoord(round(x + z/2 + kx/2),round(y + z/2 + ky/2),mz); // a Z koordináta a nagyságát adja meg
}


struct Sboxok
{
	//private: 
	Skoord k; //Azért tarton meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	Skoord szin; // Miért ne? ez is 3 :)
	Skoord f; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	Sboxok *kovet; // ki után menjen | NULL ha senki után | publikus lenne ha lehetne, de a SPECIFIKÁCIÓ szent :)

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

	void supdate(double alpha); // forgatás, mozgatás
	void srajzol(); // csak rajzolás
	Skoord getKoords(); //read only
	Skoord getSzin(); //read only
	void setKovet(Sboxok *ekovet); // write only
};

Skoord Sboxok::getKoords()
{
	return k;
}

Skoord Sboxok::getSzin()
{
	return szin;
}

void Sboxok::setKovet(Sboxok *ekovet)
{
	kovet=ekovet;
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

	Skoord a = f.lekepzes();

	if (a.x>=kx-a.z or a.x<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (a.y>=ky-a.z or a.y<0) return;

	/*stringstream str;
	str << int(k.x) << " " << int(k.y) << " " << int(k.z);
	string s = str.str(); //*/

	gout << color(szin.x,szin.y,szin.z)
		<< move_to(a.x,a.y)
		<< box(a.z,a.z);
		//<< text(s);
}





/* A JÁTÉK RÉSZE*/

struct Srekord
{	
	int pont;
	int kaja;
	int maxkaja;
	const int hosszszorzo;

	Sboxok *fej;
	Sboxok *farok;
	Sboxok *target;
	Sboxok *cel;
	// A target az tárolódik a vektorban;

	Srekord(int &szin,vector<Sboxok*> &boxok,int maxkaja,int hosszszorzo) : maxkaja(maxkaja), kaja(0), pont(0), hosszszorzo(hosszszorzo)
	{
		fej = new Sboxok(Skoord(0,0,0),szin,NULL);
		boxok.push_back(fej); if (szin<3*255) szin++; else szin=0;
		farok = fej;
		target = NULL;
		cel = NULL;
	}
	
};

void pontkiir(int pont);

double update(int i,vector<Sboxok*> &boxok,Skoord eger,double alpha)
{
	if (false)
	{
			delete boxok[i];
			boxok[i] = boxok[boxok.size()-1];
			boxok.pop_back();
	}
	Skoord a = boxok[i]->getKoords().forgat(alpha).lekepzes(); a.z=0; // pontok helyzete a képernyőn
	return a|eger; //egértől való távolság
	}


void updatedraw(vector<Sboxok*> &boxok,double alpha,Skoord eger,Srekord &rekord,int &szin)
{
	//draw

	gout << color(000,000,000) 
			<< move_to(0,0) 
			<< box(kx,ky);

	gout << color(25,25,25);
	pontkiir(rekord.pont);

	//update

	while (rekord.kaja<rekord.maxkaja)
	{
		Sboxok *a = new Sboxok(Skoord(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2),szin,NULL);
		boxok.push_back(a); if (szin<3*255) szin++; else szin=0;
		rekord.kaja++;
	}

	if (rekord.target) {
		Skoord ffej = rekord.fej->getKoords().forgat(alpha).lekepzes();
		Skoord ftarget = rekord.target->getKoords().forgat(alpha).lekepzes();

	//draw

		gout << color(255,255,255)
			<< move_to(ffej.x + ffej.z/2, ffej.y + ffej.z/2) // a Z koordináta a bagyságukat adja meg
			<< line_to(ftarget.x + ftarget.z/2, ftarget.y + ftarget.z/2);
	}

	//update

	int mintav = nagyszam;
	rekord.target = NULL;


	for (int i = 0; i < boxok.size();i++)
	{
		boxok[i]->supdate(alpha); //update
		boxok[i]->srajzol(); //draw
		double tav = update(i,boxok,eger,alpha); //update
		if (tav<mintav and rekord.fej!=boxok[i]) {mintav=tav; rekord.target=boxok[i];} //update
	}

	//update

	rekord.fej->setKovet(rekord.target);
	

	//draw

	gout << refresh;

}



int main()
{
	srand (time(NULL));

	gout.open(kx,ky,teljes);

	gin.timer(20);

	double alpha 		= 0;
	double rpx			= 0;
	const double mertek = 0.03;

	Skoord eger			  (0,0,0); 			// A Z koordináta nem használt
	int szin 			= rand()%(3*255);

	vector<Sboxok*> boxok;

	Srekord	rekord		  (szin,boxok,9,10);


	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			alpha+=rpx; // forgatás
			updatedraw(boxok,alpha,eger,rekord,szin);
		
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
			eger.x=ev.pos_x;
			eger.y=ev.pos_y;
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
