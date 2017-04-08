#ifndef _ABLAK_	//ujabb definíció és fordítási hiba elkerülésére
#define _ABLAK_

#include "szin.hpp"
#include "kamera.hpp"

class ABLAK : public OBJ
{
	protected:

	SZIN szin; //szín
	unsigned int kx,ky; // kép x,y

	public:

	ABLAK(double x,double y, double sx, double sy, unsigned int allapot, unsigned int kx, unsigned int ky)
		:  OBJ(x,y,sx,sy,allapot), kx(kx), ky(ky)
	{
		szin = SZIN(0,0,0);
	}
	ABLAK(double x,double y, double sx, double sy, unsigned int allapot, SZIN szin)
		: OBJ(x,y,sx,sy,allapot), szin(szin)
	{
		kx=0;
		ky=0;
	}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double XX, double YY, KAMERA kamera) const;
};

void ABLAK::srajzol(canvas &Tkepek, double X0, double Y0, double XX, double YY,KAMERA kamera) const
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x+X0;uy=y+Y0;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getCoords(ux,uy);
	if (ux+usx<X0 or ux>X0+XX or uy+usy<Y0 or uy>Y0+YY) return;
	if (ux+usx>X0+XX) {usx=X0+XX-ux;}
	if (ux<X0) {usx+=ux-X0; ukx-=ux; ux=X0;}
	if (uy+usy>Y0+YY) {usy=Y0+YY-uy;}
	if (uy<Y0) {usy+=uy-Y0; uky-=uy; uy=Y0;}
	if (kx==0 and ky==0) 
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy); // szín
	else 
		gout << stamp(Tkepek,ukx,uky,usx,usy,ux,uy); // A canvasra nem lehet stampelni? ezért így van megoldva a "kilógás"
	
	for (int i = 0; i < objektumok.size();++i) // Saját objektumai
	{
		if (objektumok[i]->allapot==0 or objektumok[i]->allapot==1) objektumok[i]->srajzol(Tkepek,ux,uy,usx,usy,kamera); // tartalma kirajzolása
	}
	
}

#endif