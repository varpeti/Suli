#ifndef _WIDGETS_	//ujabb definíció és fordítási hiba elkerülésére
#define _WIDGETS_

#include "env.hpp"

class WIDGETS : public ENV::SPRITE {
		SZIN keretszin;
	public:
		WIDGETS(double x,double y, unsigned int kx, unsigned int ky, double sx, double sy)
			: SPRITE(x,y,0,kx,ky,sx,sy)
		{}
		//void srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera);
};

/*void WIDGETS::srajzol(canvas &TS,unsigned int KEPERNYOSZELESSEG,unsigned int KEPERNYOMAGASSAG,KAMERA kamera)
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
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy);
	else 
		gout << stamp(TS,ukx,uky,usx,usy,ux,uy);
}*/

#endif