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
	};
	vector<SPRITE> SPRITEOK;
	void newsprite(int x, int y);
	
protected:
	unsigned int KEPERNYOSZELESSEG;
	unsigned int KEPERNYOMAGASSAG;
	unsigned int TERULETSZELESSEG;
	unsigned int TERULETMAGASSAG;
	canvas TERULET;
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


#endif