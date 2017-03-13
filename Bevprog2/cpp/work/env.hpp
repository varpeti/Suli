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

struct SZIN
{
	unsigned char rr,gg,bb;

	SZIN(unsigned char rr,unsigned char gg,unsigned char bb) : rr(rr), gg(gg), bb(bb) {};

	SZIN() : rr(0), gg(0), bb(0) {};
};


/* CLASS 	*/

class ENV
{
public:
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag);
	~ENV();

	void kirajzol();
	bool spriteok_beolvas(const char *fname); // BMP-ből olvassa be az összes spriteot

	event ev;
	KAMERA kamera;
	
protected:

	struct SPRITE
	{
		double x,y; // kooridiáták lehet negatív is
		unsigned int allapot; // 255 törölhető, 0 látszik updetelődik, 1 lát, 2 update, else semmi
		unsigned int sx,sy; // szélesség magasság
		SZIN szin; //szín
		unsigned int kx,ky; // sprite x,y
		double vx,vy; // sebesség
		SPRITE *utk;

		void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera);
		void supdate(vector<SPRITE*> &SPRITEOK);

		SPRITE(double x,double y,unsigned int allapot, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
			: x(x), y(y), allapot(allapot), kx(kx), ky(ky), sx(sx), sy(sy)
		{
			szin = SZIN(0,0,0);
			vx=0;
			vy=0;
			utk=NULL;
		}
		SPRITE(double x,double y,unsigned int allapot,unsigned int sx, unsigned int sy,SZIN szin)
			: x(x), y(y), allapot(allapot), sx(sx), sy(sy), szin(szin)
		{
			kx=0;
			ky=0;
			vx=0;
			vy=0;
			utk=NULL;
		}

	};
	canvas TSPRITEOK;	//az összes sprite képét ide olvasom be

	unsigned int KEPERNYOSZELESSEG;
	unsigned int KEPERNYOMAGASSAG;
public:
	vector<SPRITE*> SPRITEOK; // Az összes sprite

	SPRITE *newSprite(double x, double y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy); // spriteos
	SPRITE *newSprite(double x, double y, unsigned int sx, unsigned int sy,SZIN szin); // színes

	// Azért nem hülyeség a getter és setter mert SEXYBB mint a mezők :D | Egyébként az adatok főleg párosával vannak.
	void setSpriteSebesseg(SPRITE *sp,double vx,double vy);
	void getSpriteSebesseg(SPRITE *sp,double &vx,double &vy);
	void setSpritePosition(SPRITE *sp,double x,double y);
	void getSpritePosition(SPRITE *sp,double &x,double &y);
	void setSpriteAllapot(SPRITE *sp,unsigned char allapot);
	void getSpriteAllapot(SPRITE *sp,unsigned char &allapot);

	bool SpriteBenneVan(SPRITE *sp, double px, double py);
	SPRITE *utkozott(SPRITE *sp);
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
}

ENV::~ENV() //dest
{

}

ENV::SPRITE *ENV::newSprite(double x, double y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
{
	SPRITE *sp = new SPRITE(x,y,0,kx,ky,sx,sy);
	SPRITEOK.push_back(sp);
	return sp;
}

ENV::SPRITE *ENV::newSprite(double x, double y, unsigned int sx, unsigned int sy, SZIN szin)
{
	SPRITE *sp = new SPRITE(x,y,0,sx,sy,szin);
	SPRITEOK.push_back(sp);
	return sp;
}

void ENV::kirajzol()
{
	gout << color(0,0,0) << move_to(0,0) << box(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);

	for (int i = 0; i < SPRITEOK.size();)
	{
		if (SPRITEOK[i]->allapot==0 or SPRITEOK[i]->allapot==2) SPRITEOK[i]->supdate(SPRITEOK);
		if (SPRITEOK[i]->allapot==0 or SPRITEOK[i]->allapot==1) SPRITEOK[i]->srajzol(TSPRITEOK,KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,kamera);
		if (SPRITEOK[i]->allapot==255) 
		{ //törlés
			delete SPRITEOK[i];
			SPRITEOK[i] = SPRITEOK[SPRITEOK.size()-1];
			SPRITEOK.pop_back();
		}
		else ++i; // Ha nem törlődik, a következőre lép
	}

	gout << refresh;
}

void ENV::SPRITE::srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera)
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x;uy=y;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getCoords(ux,uy);
	if (ux+usx<0 or ux>KEPERNYOSZELESSEG or uy+usy<0 or uy>KEPERNYOMAGASSAG) return;
	if (ux+usx>KEPERNYOSZELESSEG) {usx=KEPERNYOSZELESSEG-ux;}
	if (ux<0) {usx+=ux; ukx-=ux; ux=0;}
	if (uy+usy>KEPERNYOMAGASSAG) {usy=KEPERNYOMAGASSAG-uy;}
	if (uy<0) {usy+=uy; uky-=uy; uy=0;}
	if (kx==0 and ky==0) 
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy); // szín
	else 
		gout << stamp(TS,ukx,uky,usx,usy,ux,uy); // A canvasra nem lehet stampelni? ezért így van megoldva a "kilógás"
}

void ENV::SPRITE::supdate(vector<SPRITE*> &SPRITEOK)
{
	x+=vx;
	y+=vy;
	utk = NULL;

	auto bennevan = [](double px, double py, double mx, double my, int msx, int msy) 
	{ 
		if (px>=mx and px<=mx+msx and py>=my and py<=my+msy) return true;
		return false;
	};

	for (int i = 0; i < SPRITEOK.size(); ++i)
		if ( (SPRITEOK[i]->allapot==0 or SPRITEOK[i]->allapot==2) and SPRITEOK[i]!=this)
		{
			if (bennevan(x,y,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x+sx,y,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x,y+sy,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or bennevan(x+sx,y+sy,SPRITEOK[i]->x,SPRITEOK[i]->y,SPRITEOK[i]->sx,SPRITEOK[i]->sy) or
				bennevan(SPRITEOK[i]->x,SPRITEOK[i]->y,x,y,sx,sy) or bennevan(SPRITEOK[i]->x+SPRITEOK[i]->sx,SPRITEOK[i]->y,x,y,sx,sy) or bennevan(SPRITEOK[i]->x,SPRITEOK[i]->y+SPRITEOK[i]->sy,x,y,sx,sy) or bennevan(SPRITEOK[i]->x+SPRITEOK[i]->sx,SPRITEOK[i]->y+SPRITEOK[i]->sy,x,y,sx,sy)) 
				{utk=SPRITEOK[i];}
		}
}

void ENV::setSpriteSebesseg(SPRITE *sp,double vx,double vy)
{
	if (!sp) return;
	sp->vx=vx;
	sp->vy=vy;
}

void ENV::getSpriteSebesseg(SPRITE *sp,double &vx,double &vy)
{
	if (!sp) return;
	vx=sp->vx;
	vy=sp->vy;
}

void ENV::setSpritePosition(SPRITE *sp,double x,double y)
{
	if (!sp) return;
	sp->x=x;
	sp->y=y;
}

void ENV::getSpritePosition(SPRITE *sp,double &x,double &y)
{
	if (!sp) return;
	x=sp->x;
	y=sp->y;
}

void ENV::setSpriteAllapot(SPRITE *sp,unsigned char allapot)
{
	if (!sp) return;
	sp->allapot=allapot;
}

void ENV::getSpriteAllapot(SPRITE *sp,unsigned char &allapot)
{
	if (!sp) return;
	allapot=sp->allapot;
}


ENV::SPRITE *ENV::utkozott(SPRITE *sp)
{
	if (!sp) return NULL;
	return sp->utk;
}

bool ENV::SpriteBenneVan(SPRITE *sp, double px, double py)
{ 
	if (!sp) return false;
	if (px>=sp->x and px<=sp->x+sp->sx and py>=sp->y and py<=sp->y+sp->sy) return true;
	return false;
};


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