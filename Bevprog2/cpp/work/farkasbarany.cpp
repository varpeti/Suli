#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "time.h"
#include "math.h"
#include "iostream"

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 700;
const bool teljes = false;
const int nagyszam = kx+ky;
const int megevesitav = 10;
const int egyedf = 10;
const int egyedb = 50;

const double baranyseb = 3.4;
const double baranyteh = 60;
const double farkasseb = 3.8;
const double farkasteh = 75;

bool DEBUG = false;

struct Sboxok
{
	double x,y;
	double vx,vy;
	double sx,sy;
	double tehetetlenseg;
	double maxseb;
	int szam;
	unsigned char rr,gg,bb;

	Sboxok (double x, double y, double maxseb, double tehetetlenseg, int szin)
	: x(x), y(y), sx(10), sy(10), vx(0), vy(0), maxseb(maxseb), tehetetlenseg(tehetetlenseg), szam(0)
	{
		if (szin<=255) 					{rr=255-(szin-0*255); 	gg=(szin-0*255); 		bb=000;} 				else
		if (szin>255 and szin<=2*255) 	{rr=000; 				gg=255-(szin-1*255); 	bb=(szin-1*255);} 		else
		if (szin>2*255) 				{rr=(szin-2*255); 		gg=000; 				bb=255-(szin-2*255);}
	};

	void supdate(double mx, double my, bool fele);
	void srajzol();
};

void Sboxok::supdate(double mx, double my, bool fele) 
{	
	if (mx!=-1) {
		double a = mx-x;
		double b = my-y;
		double h = ( sqrt(a*a+b*b) )/(rand()%10+3)*tehetetlenseg; if (h==0) h=1;
		if (fele) {vx+=a/h;vy+=b/h;}
		else {vx-=a/h;vy-=b/h;}
	
		if (vx>maxseb) vx=maxseb; else if (vx<-maxseb) vx=-maxseb;
		if (vy>maxseb) vy=maxseb; else if (vy<-maxseb) vy=-maxseb;
	}

	x+=vx;
	y+=vy;

	if (x+sx<0) x=kx-1; if (x>kx) x=1;
	if (y+sy<0) y=ky-1; if (y>ky) y=1;

	if (DEBUG and mx!=-1)
	{
		if (!fele) gout << color(0,255,0); else gout << color(255,0,0);
		gout << move_to(x,y) << line_to(mx,my);
	}
}

void Sboxok::srajzol()
{
	// Hogy ki tudjon lógi a képernyőről
	double ux,uy,usx,usy,ukx,uky;
	ux=x;uy=y;usx=sx;usy=sy;
	if (ux+usx<0 or ux>kx or uy+usy<0 or uy>ky) return;
	if (ux+usx>kx) {usx=kx-ux;}
	if (ux<0) {usx+=ux; ux=0;}
	if (uy+usy>ky) {usy=ky-uy;}
	if (uy<0) {usy+=uy; uy=0;}
	gout << color(rr,gg,bb) << move_to(ux,uy) << text(to_string(szam));
}

double tavolsag(Sboxok *barany,Sboxok *farkas)
{	

	double tav = sqrt( (farkas->x-barany->x)*(farkas->x-barany->x)+(farkas->y-barany->y)*(farkas->y-barany->y) );
	if (tav>ky/2) tav=nagyszam;
	return tav;
}



void updatedraw(vector<Sboxok*> &farkasok,vector<Sboxok*> &baranyok)
{
	// Ezt a 2 ciklust lehetne egybe de így átláthatób.

	for (int i = 0; i < farkasok.size(); ++i)
	{	
		int min = -1; // A legközelebbi bárány | azért nem mutató mert a megevéshez ID kell;
		double mtav = nagyszam; //ekkora távolságra nem lehetnek
		for (int j = 0; j < baranyok.size(); ++j)
		{
			double tav = tavolsag(baranyok[j],farkasok[i]);
			if (tav<mtav) {mtav=tav,min=j;}
		}

		if (min>-1) // Ha van bárány
		{
			if (mtav<megevesitav) { // törli ha megette
				delete baranyok[min];
				baranyok[min] = baranyok[baranyok.size()-1];
				baranyok.pop_back();
				farkasok[i]->szam++; // Növeli a farkas számlálóját
			}else
				farkasok[i]->supdate(baranyok[min]->x,baranyok[min]->y,true); // átadja merre van | true = felé megy
		}else //Nem talált célt, lehet nincs bárány?
			if (baranyok.size()==0) 
				for (int i = 0; i < egyedb; ++i){baranyok.push_back(new Sboxok(rand()%kx,rand()%ky,baranyseb,baranyteh,rand()%50+255));} //új bárányok hozzáadása
			else
				farkasok[i]->supdate(-1,-1,true); //ha nincs cél, de még van bárány, eddigi irány folytatása

		farkasok[i]->srajzol();
	}

	for (int i = 0; i < baranyok.size(); ++i)
	{
		Sboxok *min = 0; // A legközelebbi farkas
		double mtav = nagyszam; 
		for (int j = 0; j < farkasok.size(); ++j)
		{
			double tav = tavolsag(baranyok[i],farkasok[j]);
			if (tav<mtav) {mtav=tav,min=farkasok[j];}
		}

		if (min)
			baranyok[i]->supdate(min->x,min->y,false); // ha van közelben farkas
		else
			baranyok[i]->supdate(rand()%kx,rand()%ky,false); // Ha nincs, random mozgás
		baranyok[i]->srajzol();
	}
}


int main()
{
	srand (time(NULL));
	gout.open(kx,ky,teljes);

	//gout.showmouse(false);

	vector<Sboxok*> farkasok;
	vector<Sboxok*> baranyok;

	for (int i = 0; i < egyedf; ++i) //Létrehzom a bárányokat és a farkasokat
	{
		Sboxok *farkas = new Sboxok(rand()%kx,rand()%ky,farkasseb,farkasteh,rand()%50); // x, y, maximum sebesség, tehetetlenség, szín

		farkasok.push_back(farkas);
	}

	for (int i = 0; i < egyedb; ++i)
	{
		Sboxok *barany = new Sboxok(rand()%kx,rand()%ky,baranyseb,baranyteh,rand()%50+255); // x, y, maximum sebesség, tehetetlenség, szín

		baranyok.push_back(barany);
	}

	gin.timer(20);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box(kx,ky);

			updatedraw(farkasok,baranyok);

			gout << refresh;
		}
	}
	while(baranyok.size()>0)
	{
		delete baranyok[baranyok.size()-1];
		baranyok.pop_back();
	}
	while(farkasok.size()>0)
	{
		delete farkasok[farkasok.size()-1];
		farkasok.pop_back();
	}
	return 0;
}