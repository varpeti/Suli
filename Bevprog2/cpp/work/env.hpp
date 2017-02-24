#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "graphics.hpp"
#include "sstream"
#include "fstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

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

	bool sprite(string id, int x, int y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy); // látható és updetelődik
	bool newsprite(string id, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy); // nem látható és nem updatelődik
	void kirajzol();
	bool spriteok_beolvas(const char *fname); // BMP-ből olvassa be az összes spriteot

	event ev;
	
protected:

	struct SPRITE
	{
		string id; // az id-je
		int x,y; // kooridiáták lehet negatív is
		unsigned char allapot; // -1 törölhető, 0 látszik updetelődik, 1 lát, 2 update, <3 semmi
		unsigned int kx,ky,sx,sy; // sprite x,y és szélesség magasság

		void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG);
		void supdate();
		SPRITE(string uid,int ux,int uy,unsigned char uallapot, unsigned int ukx, unsigned int uky, unsigned int usx, unsigned int usy)
		{
			id=uid;
			x=ux;
			y=uy;
			allapot=uallapot;
			kx=ukx;
			ky=uky;
			sx=usx;
			sy=usy;
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

bool ENV::newsprite(string id, int x,int y, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
{
	for (SPRITE i:SPRITEOK) if (i.id==id) return false; // ha létezik ilyen idvel kilép
	SPRITE sp(id,x,y,0,kx,ky,sx,sy);
	SPRITEOK.push_back(sp);
	return true;
}

bool ENV::newsprite(string id, unsigned int kx, unsigned int ky, unsigned int sx, unsigned int sy)
{
	for (SPRITE i:SPRITEOK) if (i.id==id) return false;
	SPRITE sp(id,0,0,3,kx,ky,sx,sy); // nem jelenek meg nem updatelődik
	SPRITEOK.push_back(sp);
	return true;
}

void ENV::kirajzol()
{
	for (vector<SPRITE>::iterator i=SPRITEOK.begin(); i!=SPRITEOK.end();)
	{
		if (i->allapot==0 or i->allapot==2) i->supdate();
		if (i->allapot==0 or i->allapot==1) i->srajzol(TSPRITEOK,KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
		if(i->allapot==-1) i = SPRITEOK.erase(i);
		else ++i;
	}

	gout << refresh;
}

void ENV::SPRITE::srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG)
{
	if (x+sx>KEPERNYOSZELESSEG) {sx=KEPERNYOSZELESSEG-kx;}
	if (x<0) {sx+=x; kx-=x; x=0;}
	if (y+sy>KEPERNYOMAGASSAG) {sy=KEPERNYOMAGASSAG-ky;}
	if (y<0) {sy+=y; ky-=y; y=0;}
	gout << stamp(TS,kx,ky,sx,sy,x,y); // A canvasra nem lehet stampelni? ezért így van megoldva a "kilógás"
}

void ENV::SPRITE::supdate()
{

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