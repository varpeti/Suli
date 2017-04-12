#ifndef _STATTEXT_	//ujabb definíció és fordítási hiba elkerülésére
#define _STATTEXT_

#include "ablak.hpp"


using namespace genv;

class STATTEXT : public ABLAK
{
	protected:

	string szoveg;
	SZIN szin2;

	public:

	STATTEXT(double x, double y, unsigned int allapot, SZIN szin, SZIN szin2, string szoveg)
		: ABLAK(x,y,gout.twidth(szoveg)*1.1,gout.cascent()*1.1,allapot,szin,false), szin2(szin2), szoveg(szoveg)
	{}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera) const;
	virtual bool shandle(event ev, double X0, double Y0, KAMERA kamera) {};
};

void STATTEXT::srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera) const
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x+X0;uy=y+Y0-gout.cascent()/2;usx=sx;usy=sy+gout.cascent()/2;ukx=kx;uky=ky; // A stattext nem a bal felős sarka alapján rajzol
	kamera.getKamCoords(ux,uy);
	if (ux+usx<Xb or ux>Xb+Xj or uy<Yb or uy+usy>Yb+Yj) return; // Akkor is kilép ha felül vagy alul kilógna.
	if (ux+usx>Xb+Xj) {usx=Xb+Xj-ux;}
	if (ux<Xb) {usx+=ux-Xb; ukx-=ux; ux=Xb;}
	if (uy+usy>Yb+Yj) {usy=Yb+Yj-uy;}
	if (uy<Yb) {usy+=uy-Yb; uky-=uy; uy=Yb;} 

	gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy);
	string ki = szoveg;
	while (usx<gout.twidth(ki)) // Mindig a szöveg vége veszik el.
	{
		ki = ki.substr(0, ki.size()-1);
	}
	gout << color(szin2.rr,szin2.gg,szin2.bb) << move_to(ux,uy+gout.cascent()) << text(ki);	
}

#endif