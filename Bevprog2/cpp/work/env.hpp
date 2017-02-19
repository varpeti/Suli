#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "../graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"

/* DEKRALÁCIÓK	*/

/* STRUCTOK */

struct SP
{
	private:
		int		SP_X;		//sprite	x helyzete a képernyõn
		int		SP_Y;		//			y helyzet
		int		SP_SZ;		//			szélesség pixelekben
		int		SP_M;		//			magasság pixelekben
		char	SP_AN;		//			aktuális képpozíció
		char	SP_ANMAX;	//			maximum ennyi képpozíció van
		char	SP_SEB_X;	//			x irányú mozgás sebessége
		char	SP_SEB_Y;	//			y
		int		SP_KEPE;	//			melyik betöltött képen van a sprite rajza
		int		SP_KEP_X;	//			a képen az x helyzet kiralyzoláshoz
		int		SP_KEP_Y;	//			a képen az y helyzet kiralyzoláshoz
		ini		SP_AL_X;	//          a képen az x helyzet 
		int		SP_AL_Y;	//          a képen az y helyzet 
		int		SP_FX;		//			forrópont x
		int		SP_FY;		//			forrópont y
		int		SP_XVY;		//          x vagy y irányba van az animáció folytatása a betöltött képen

	public:
		//SP();
		//~SP();
		//void rajzol();

};

/* CLASS 	*/

class ENV
{
public:
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	~ENV();
	void frissit();
	void rajzol();
	
	
protected:
	std::vector<SP> spritok;

};

/* MEGVALÓSÍTÁS */

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo) //konst
{

}

ENV::~ENV() //dest
{

}


void ENV::init()
{
	srand (time(NULL));		//seed időalapján
	
}


#endif