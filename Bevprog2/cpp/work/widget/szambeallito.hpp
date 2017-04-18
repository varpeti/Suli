#ifndef _SZAMBEALLITO_	//ujabb definíció és fordítási hiba elkerülésére
#define _SZAMBEALLITO_

#include "szambox.hpp"

using namespace genv;

class SZAMBEALLITO : public ABLAK
{
	protected:
		SZIN szin2;
		double szam;
		double A;
		double B;
		unsigned int size;

	public:

		SZAMBEALLITO(double x, double y, double A, double B, SZIN szin, SZIN szin2, double bszam=0, unsigned int size=8)
			: ABLAK(x,y,gout.twidth("0")*(size+2)+TEXT_RAHAGYAS*3+gout.cascent(),(gout.cascent()+TEXT_RAHAGYAS*5)*2,szin,true), szin2(szin2), A(A), B(B), szam(bszam>A ? bszam<B ? bszam : B : A)
		{
			objektumok.push_back( new STATTEXT(gout.twidth("0")*size+TEXT_RAHAGYAS*3,gout.cascent()/2+TEXT_RAHAGYAS,szin2,szin," + ") );
			objektumok.push_back( new STATTEXT(gout.twidth("0")*size+TEXT_RAHAGYAS*3,gout.cascent()+TEXT_RAHAGYAS*9,szin2,szin," - ") );
			objektumok.push_back( new SZAMBOX(TEXT_RAHAGYAS,(gout.cascent()+TEXT_RAHAGYAS*4),A,B,szin,szin2,szam,size) );
		}

		bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
		void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
		void getter(ostream& ki) const;
};

bool SZAMBEALLITO::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_key)
	{
		objektumok[2]->supdate(ev,X0+x,Y0+y,kamera); // A SZAMBOX
		return true; // Elfogja a karaktereket.
	}else if (ev.button==btn_left) // Egér
	{
		double ux,uy; // Kamera elmozdulás miatt kellenek.
		ux=x+X0;uy=y+Y0;
		kamera.getKamCoords(ux,uy);
		if (objektumok[0]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {ev.type=ev_key; ev.keycode=key_up; objektumok[2]->supdate(ev,X0+x,Y0+y,kamera);return true;}
		if (objektumok[1]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {ev.type=ev_key; ev.keycode=key_down; objektumok[2]->supdate(ev,X0+x,Y0+y,kamera);return true;}
	}
	return false; // Nem fogja el, (pl így el lehet húzni az alatta lévő ablakkal együtt.)
}

void SZAMBEALLITO::getter(ostream& ki) const 
{
	objektumok[2]->getter(ki);
};



#endif