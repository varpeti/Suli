#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "../graphics.hpp"
#include "sstream"
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
		unsigned char allapot;
		void srajzol();
	};
	vector<SPRITE> SPRITEOK;
	void newsprite(int x, int y);
	void kirajzol();
	
protected:
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
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=kepernyomagassag;
	KEPERNYOSZELESSEG=kepernyoszelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	if (magassag>kepernyomagassag) TERULETMAGASSAG=magassag; else TERULETMAGASSAG=kepernyomagassag;
	if (szelesseg>kepernyoszelesseg) TERULETMAGASSAG=szelesseg; else TERULETMAGASSAG=kepernyoszelesseg;
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
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
		//i->supdate();
		i->srajzol();
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


#endif