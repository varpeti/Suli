#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "graphics.hpp"
#include "sstream"
#include "fstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "kamera.hpp"
#include "iostream"
#include "algorithm"

using namespace genv;
using namespace std;

/* DEKRALÁCIÓK	*/

/* STRUCTOK */


/* CLASS 	*/

class ENV
{
public:
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag);
	~ENV();

	bool newSprite(long long int id, double x, double y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy); // látható és updetelődik
	bool newSprite(long long int id, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy); // nem látható és nem updatelődik
	void kirajzol();
	bool spriteok_beolvas(const char *fname); // BMP-ből olvassa be az összes spriteot

	bool setSpriteSebesseg(long long int id,double vx,double vy);
	bool getSpriteSebesseg(long long int id,double &vx,double &vy);
	bool setSpritePosition(long long int id,double x,double y);
	bool getSpritePosition(long long int id,double &x,double &y);
	bool setSpriteAllapot(long long int id,unsigned char allapot);
	bool getSpriteAllapot(long long int id,unsigned char &allapot);

	long long int utkozott(long long int aid);

	event ev;
	KAMERA kamera;
	
protected:

	struct SPRITE
	{
		long long int id; // az id-je (0 nem lehet!)
		double x,y; // kooridiáták lehet negatív is
		unsigned int allapot; // -1 törölhető, 0 látszik updetelődik, 1 lát, 2 update, else semmi
		unsigned int kx,ky,sx,sy; // sprite x,y és szélesség magasság
		double vx,vy; // sebesség
		long long utk;

		void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera);
		void supdate(vector<SPRITE> &SPRITEOK);
		SPRITE(long long int uid,double ux,double uy,unsigned int uallapot, unsigned int ukx, unsigned int uky, unsigned int usx, unsigned int usy)
		{
			id=uid;
			x=ux;
			y=uy;
			allapot=uallapot;
			kx=ukx;
			ky=uky;
			sx=usx;
			sy=usy;
			vx=0;
			vy=0;
			utk=0;
		}
	};
	canvas TSPRITEOK;	//az összes sprite képét ide olvasom be
	vector<SPRITE> SPRITEOK;

	unsigned int KEPERNYOSZELESSEG;
	unsigned int KEPERNYOMAGASSAG;
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	SPRITE b(0,0,0,3,0,0,0,0); SPRITEOK.push_back(b);
	
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	SPRITE b(0,0,0,3,0,0,0,0); SPRITEOK.push_back(b);
}

ENV::~ENV() //dest
{

}

bool ENV::newSprite(long long int id, double x, double y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
{
	if (id==0) return false;
	for (SPRITE i:SPRITEOK) if (i.id==id) return false; // ha létezik ilyen idvel kilép
	SPRITE sp(id,x,y,0,kx,ky,sx,sy);
	SPRITEOK.push_back(sp);
	return true;
}

bool ENV::newSprite(long long int id, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
{
	if (id==0) return false;
	for (SPRITE i:SPRITEOK) if (i.id==id) return false;
	SPRITE sp(id,0,0,3,kx,ky,sx,sy); // nem jelenek meg nem updatelődik
	SPRITEOK.push_back(sp);
	return true;
}

void ENV::kirajzol()
{
	gout << color(0,0,0) << move_to(0,0) << box(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);

	for (vector<SPRITE>::iterator i=SPRITEOK.begin(); i!=SPRITEOK.end();)
	{
		if (i->allapot==0 or i->allapot==2) i->supdate(SPRITEOK);
		if (i->allapot==0 or i->allapot==1) i->srajzol(TSPRITEOK,KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,kamera);
		if (i->allapot==-1) {std::swap(*i, SPRITEOK.back()); SPRITEOK.pop_back(); cout << "torolve: " << i->id << endl;}// ezt lehetne kicserél popback re cserélni
		else ++i;
		cout << i->allapot << " " << i->id << endl;
	}

	gout << refresh;
}

void ENV::SPRITE::srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera)
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x;uy=y;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getCoords(ux,uy);
	if (ux+usx<0 or ux>KEPERNYOSZELESSEG or uy+usy<0 or uy>KEPERNYOMAGASSAG) return;
	if (ux+usx>KEPERNYOSZELESSEG) {usx=KEPERNYOSZELESSEG-ukx;}
	if (ux<0) {usx+=ux; ukx-=ux; ux=0;}
	if (uy+usy>KEPERNYOMAGASSAG) {usy=KEPERNYOMAGASSAG-uky;}
	if (uy<0) {usy+=uy; uky-=uy; uy=0;}
	gout << stamp(TS,ukx,uky,usx,usy,ux,uy); // A canvasra nem lehet stampelni? ezért így van megoldva a "kilógás"
}

void ENV::SPRITE::supdate(vector<SPRITE> &SPRITEOK)
{
	//cout << id << " " << vx << " " << vy << endl;
	x+=vx;
	y+=vy;
	utk = 0;

	auto bennevan = [](double px, double py, double mx, double my, int msx, int msy) 
	{ 
		if (px>=mx and px<=mx+msx and py>=my and py<=my+msy) return true;
		return false;
	};

	for (SPRITE &sp:SPRITEOK)
		if (sp.id!=id and (sp.allapot==0 or sp.allapot==2))
		{
			if (bennevan(x,y,sp.x,sp.y,sp.sx,sp.sy) or bennevan(x+sx,y,sp.x,sp.y,sp.sx,sp.sy) or bennevan(x,y+sy,sp.x,sp.y,sp.sx,sp.sy) or bennevan(x+sx,y+sy,sp.x,sp.y,sp.sx,sp.sy)) utk=sp.id;
			else if (bennevan(sp.x,sp.y,x,y,sx,sy) or bennevan(sp.x+sp.sx,sp.y,x,y,sx,sy) or bennevan(sp.x,sp.y+sp.sy,x,y,sx,sy) or bennevan(sp.x+sp.sx,sp.y+sp.sy,x,y,sx,sy)) utk=sp.id;
		}
	if (utk) cout << "utk: " << id << " " << utk << endl;
}

bool ENV::setSpriteSebesseg(long long int id,double vx,double vy)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			sp.vx=vx;
			sp.vy=vy;
			return true;
		}
	return false;
}

bool ENV::getSpriteSebesseg(long long int id,double &vx,double &vy)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			vx=sp.vx;
			vy=sp.vy;
			return true;
		}
	return false;
}

bool ENV::setSpritePosition(long long int id,double x,double y)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			sp.x=x;
			sp.y=y;
			return true;
		}
	return false;
}

bool ENV::getSpritePosition(long long int id,double &x,double &y)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			x=sp.x;
			y=sp.y;
			return true;
		}
	return false;
}

bool ENV::setSpriteAllapot(long long int id,unsigned char allapot)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			sp.allapot=allapot;
			return true;
		}
	return false;
}

bool ENV::getSpriteAllapot(long long int id,unsigned char &allapot)
{
	for (SPRITE &sp:SPRITEOK)
		if (sp.id==id) {
			allapot=sp.allapot;
			return true;
		}
	return false;
}


long long int ENV::utkozott(long long int aid)
{
	for (SPRITE &sp:SPRITEOK)
		if (aid==sp.id) {return sp.utk;}
	return 0;
}


bool ENV::spriteok_beolvas(const char *fname) // CSAK azért is BMPből.
{
	/*
	ifstream be(fname);
	if (!be.is_open()) return;
	int kx,ky;
	be >> kx;
	be >> ky;
	TSPRITEOK.open(kx,ky); //TSPRITEOK.load_font("font.ttf",12,true);
	for (int i = 0; i < ky; ++i)
	{
		for (int j = 0; j < kx; ++j)
		{
			int rr; be >> rr;
			int gg; be >> gg;
			int bb; be >> bb;
			TSPRITEOK << move_to(j,i) << color(rr,gg,bb) << dot;
		}
	}
	be.close();*/

	FILE* f = fopen(fname, "rb"); if (!f) return false;
	unsigned char info[54] = {0}; // 54 byte: az infók
	fread(info, sizeof(unsigned char), 54, f); 

	unsigned int width = *(int*)&info[18]; //18. szélesség
	unsigned int height = *(int*)&info[22]; //22. magasság

	unsigned int size = 3 * width * height; // 3 byte pixelenként
	unsigned char* data = new unsigned char[size]; // lefoglalás
	fread(data, sizeof(unsigned char), size, f); // beolvasás egyszerre / csak ha nincsenek színtérinformációk, különben csúszik
	fclose(f);

	TSPRITEOK.open(width,height); // canvas megnyitása
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) //y
	{
		for (unsigned int j = 0; j < width; j++) //x
		{
			unsigned int bb = data[k]; k++; // Igen a mikrofos BBGGRR formátumot használ
			unsigned int gg = data[k]; k++;
			unsigned int rr = data[k]; k++;
			TSPRITEOK << move_to(j,height-i) << color(rr,gg,bb) << dot; // ja és fejjel lefele (MIÉRT???)
		}
	}
	delete data; //Nem használt memória felszabadítása
	return true;
}


#endif