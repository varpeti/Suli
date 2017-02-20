#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "../graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

using namespace genv;

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
	void init();
	
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
	KEPERNYOMAGASSAG=kepernyomagassag;
	KEPERNYOSZELESSEG=kepernyoszelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	if (magassag>kepernyomagassag) TERULETMAGASSAG=magassag; else TERULETMAGASSAG=kepernyomagassag;
	if (szelesseg>kepernyoszelesseg) TERULETMAGASSAG=szelesseg; else TERULETMAGASSAG=kepernyoszelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, unsigned int kepernyoszelesseg, unsigned int kepernyomagassag)
{
	KEPERNYOMAGASSAG=kepernyomagassag;
	KEPERNYOSZELESSEG=kepernyoszelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	if (magassag>kepernyomagassag) TERULETMAGASSAG=magassag; else TERULETMAGASSAG=kepernyomagassag;
	if (szelesseg>kepernyoszelesseg) TERULETMAGASSAG=szelesseg; else TERULETMAGASSAG=kepernyoszelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG,teljeskepernyo);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	KEPERNYOMAGASSAG=magassag;
	KEPERNYOSZELESSEG=szelesseg;
	gout.open(KEPERNYOSZELESSEG,KEPERNYOMAGASSAG);
	TERULETMAGASSAG=magassag;
	TERULETSZELESSEG=szelesseg;
	TERULET.open(TERULETSZELESSEG,TERULETMAGASSAG);
}

ENV::~ENV() //dest
{

}


void ENV::init()
{
	srand (time(NULL));		//seed időalapján
	
}


#endif