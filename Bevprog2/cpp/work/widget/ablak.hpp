#ifndef _ABLAK_	//ujabb definíció és fordítási hiba elkerülésére
#define _ABLAK_

#define ABLAK_RAHAGYAS 5

#include "szin.hpp"
#include "env.hpp"

using namespace genv;

class ABLAK : public OBJ
{
	protected:

	SZIN szin; //szín
	unsigned int kx,ky; // kép x,y

	public:

	ABLAK(double x, double y, double sx, double sy, unsigned int allapot, unsigned int kx, unsigned int ky, bool mozgathato=true)
		:  OBJ(x,y,sx,sy,allapot,mozgathato), kx(kx), ky(ky)
	{
		szin = SZIN(0,0,0);
	}
	ABLAK(double x, double y, double sx, double sy, unsigned int allapot, SZIN szin, bool mozgathato=true)
		: OBJ(x,y,sx,sy,allapot,mozgathato), szin(szin)
	{
		kx=0;
		ky=0;
	}

	virtual void srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera) const;
	virtual void supdate(canvas &Tkepek, double X0, double Y0, KAMERA kamera, event ev);
	virtual bool shandle(event ev, double X0, double Y0, KAMERA kamera);
};

void ABLAK::srajzol(canvas &Tkepek, double X0, double Y0, double Xb, double Yb, double Xj, double Yj, KAMERA kamera) const
{
	double ux,uy,usx,usy,ukx,uky;
	ux=x+X0;uy=y+Y0;usx=sx;usy=sy;ukx=kx;uky=ky;
	kamera.getKamCoords(ux,uy);
	if (ux+usx<Xb or ux>Xb+Xj or uy+usy<Yb or uy>Yb+Yj) return;
	if (ux+usx>Xb+Xj) {usx=Xb+Xj-ux;}
	if (ux<Xb) {usx+=ux-Xb; ukx-=ux; ux=Xb;}
	if (uy+usy>Yb+Yj) {usy=Yb+Yj-uy;}
	if (uy<Yb) {usy+=uy-Yb; uky-=uy; uy=Yb;}
	if (kx==0 and ky==0) 
		gout << color(szin.rr,szin.gg,szin.bb) << move_to(ux,uy) << box(usx,usy); // szín
	else 
		gout << stamp(Tkepek,ukx,uky,usx,usy,ux,uy); // Kép
	
	for (int i = 0; i < objektumok.size();++i) // Saját objektumai kirajzolása
	{
		if (objektumok[i]->getAllapot()==0 or objektumok[i]->getAllapot()==1) objektumok[i]->srajzol(Tkepek,x+X0,y+Y0,ux,uy,usx,usy,kamera); 
	}
	
}

void ABLAK::supdate(canvas &Tkepek, double X0, double Y0, KAMERA kamera, event ev)
{
	if (objektumok.size()==0) return;

	if (ev.type==ev_timer)
	{
		for (int i = 0; i < objektumok.size();) // Saját objektumai updatelése
		{
			if (objektumok[i]->getAllapot()==0 or objektumok[i]->getAllapot()==2) objektumok[i]->supdate(Tkepek,X0+x,Y0+y,kamera,ev);
			if (objektumok[i]->getAllapot()==255)
			{ //törlés
				delete objektumok[i];
				objektumok[i] = objektumok[objektumok.size()-1];
				objektumok.pop_back();
			}
			else ++i; // Ha nem törlődik, a következőre lép
		}
	}
}

bool ABLAK::shandle(event ev, double X0, double Y0, KAMERA kamera)
{
	if (objektumok.size()==0) return false; // Ha nincs benne semmi, az alatta lévők mozognak.

	double ux,uy,uX0,uY0; // Kamera elmozdulás miatt kellenek.
	ux=x+X0;uy=y+Y0;
	uX0=X0;uY0=Y0;

	if (objektumok[objektumok.size()-1]->shandle(ev,ux,uy,kamera)) return true; // Ha benne lévőt mozgattnak nem mozognak visszamenőleg.

	kamera.getKamCoords(ux,uy);
	kamera.getKamCoords(uX0,uY0);

	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
			for (int i = objektumok.size()-1; i >= 0; i--)
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy) and objektumok[i]->isMozgathato() and this->BenneVan(ev.pos_x-uX0,ev.pos_y-uY0)) // Az egér a belsőre kattint, mozgatható a belső, és a külsőben is benne van az egér
				{
					objektumok[i]->getPosition(ex,ey);
					ex-=ev.pos_x;
					ey-=ev.pos_y;
					lenyomva=true;
					OBJ::ObjKiemel(objektumok[i]);
					break;
				}
		if (-ev.button==btn_left) {lenyomva=false; ex=0; ey=0;} // Ha felengedi
		

		if (lenyomva) {
			double lx,ly,lsx,lsy;
			objektumok[objektumok.size()-1]->getMeret(lsx,lsy);
			lx=ev.pos_x+ex;
			ly=ev.pos_y+ey;
			if (!(lx+lsx<ABLAK_RAHAGYAS or lx>sx-ABLAK_RAHAGYAS or ly+lsy<ABLAK_RAHAGYAS or ly>sy-ABLAK_RAHAGYAS)) objektumok[objektumok.size()-1]->setPosition(lx,ly); // ameddig nyomva van, és benne van a külsőben mozog.
		}
	}
	return lenyomva;
}

#endif