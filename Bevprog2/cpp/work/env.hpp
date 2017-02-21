#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "../graphics.hpp"
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
	ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag);
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag);
	~ENV();

	struct SPRITE
	{
		int x;
		int y;
		unsigned char allapot; // -1 törölhető, 0 látszik updetelődik, 1 lát, 2 update, 3 semmi
		//canvas kep;
		int kx,ky;

		void setallapot(unsigned char al);
		unsigned char getallapot();
		void srajzol();
		void supdate();
		void beolvas(string filename);
	};
	vector<SPRITE> SPRITEOK;
	void newsprite(int x, int y);
	void kirajzol();

	event ev;
	
protected:
	canvas TERULET;
	unsigned int KEPERNYOSZELESSEG;
	unsigned int KEPERNYOMAGASSAG;
	unsigned int TERULETSZELESSEG;
	unsigned int TERULETMAGASSAG;
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag, bool teljeskepernyo)
{
	srand(time(NULL));		//seed időalapján
	KEPERNYOMAGASSAG=kepernyomagassag;
	KEPERNYOSZELESSEG=kepernyoszelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	if (magassag>kepernyomagassag) TERULETMAGASSAG=magassag; else TERULETMAGASSAG=kepernyomagassag;
	if (szelesseg>kepernyoszelesseg) TERULETMAGASSAG=szelesseg; else TERULETMAGASSAG=kepernyoszelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
	TERULET.load_font("font.ttf",12,true);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=kepernyomagassag;
	KEPERNYOSZELESSEG=kepernyoszelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	if (magassag>kepernyomagassag) TERULETMAGASSAG=magassag; else TERULETMAGASSAG=kepernyomagassag;
	if (szelesseg>kepernyoszelesseg) TERULETMAGASSAG=szelesseg; else TERULETMAGASSAG=kepernyoszelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
	TERULET.load_font("font.ttf",12,true);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
	TERULET.load_font("font.ttf",12,true);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
	TERULET.load_font("font.ttf",12,true);
}

ENV::~ENV() //dest
{

}

void ENV::newsprite(int x, int y)
{
	SPRITE sp;
	sp.x=x;
	sp.y=y;
	SPRITEOK.push_back(sp);
}

void ENV::kirajzol()
{
	for (vector<SPRITE>::iterator i=SPRITEOK.begin(); i!=SPRITEOK.end();)
	{
		//if (i->allapot==0 or i->allapot==2) i->supdate();
		if (i->allapot==0 or i->allapot==1) i->srajzol();
		if(i->allapot==-1) i = SPRITEOK.erase(i);
		else ++i;
	}
	gout << refresh;
}

void ENV::SPRITE::srajzol()
{
	gout << color(000,255,000)
		<< move_to(x,y)
		<< box(10,10);
}

void ENV::SPRITE::setallapot(unsigned char al)
{
	allapot=al;
}

unsigned char ENV::SPRITE::getallapot()
{
	return allapot;
}

void ENV::SPRITE::supdate()
{

}

void ENV::SPRITE::beolvas(string filename)
{
	ifstream be(filename);
	if (!be.is_open()) return;
	be >> kx;
	be >> ky;
	kep.open(kx,ky); kep.load_font("font.ttf",12,true);
	for (int i = 0; i < kx; ++i)
	{
		for (int j = 0; i < ky; ++j)
		{
			int rr; be >> rr;
			int gg; be >> gg;
			int bb; be >> bb;
			kep << move_to(i,j) << color(rr,gg,bb) << dot;
		}
	}
}


#endif