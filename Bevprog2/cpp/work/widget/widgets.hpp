#ifndef _WIDGETS_	//ujabb definíció és fordítási hiba elkerülésére
#define _WIDGETS_

#include "env.hpp"
#include "ablak.hpp"

class WIDGETS :   {
		SZIN keretszin;
	public:
		WIDGETS(double x,double y, unsigned int kx, unsigned int ky, double sx, double sy)
			: SPRITE(x,y,0,kx,ky,sx,sy)
		{}
		//void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera);
};


#endif