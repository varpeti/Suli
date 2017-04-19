#ifndef _KIVALASZTO_	//ujabb definíció és fordítási hiba elkerülésére
#define _KIVALASZTO_

#include "textbox.hpp"

using namespace genv;

class KIVALASZTO : public ABLAK
{
	private:
		unsigned int size2;
	public:

		KIVALASZTO(double x, double y, SZIN szin, SZIN szin2, vector<string> lista, unsigned int size2=0,unsigned int size=8)
			: ABLAK(x,y,gout.twidth("A")*size+TEXT_RAHAGYAS*3,
				(gout.cascent()+TEXT_RAHAGYAS*4)*( (size2 ? size2 : lista.size()) +2)+TEXT_RAHAGYAS,
				szin2,true), size2(size2)
		{	
			string gorget;
			while (gorget.size()<size) gorget+='-';
			objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS,szin,szin2,gorget) );
			objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS+(gout.cascent()+TEXT_RAHAGYAS*4)*(lista.size()+1),szin,szin2,gorget) );
			for (int i = 0; i < lista.size(); ++i)
			{
				while (lista[i].size()>size)
				{
					lista[i] = lista[i].substr(0, lista[i].size()-1);
				}
				while (lista[i].size()<size)
				{
					lista[i]+=' ';
				}

				objektumok.push_back( new STATTEXT(TEXT_RAHAGYAS,TEXT_RAHAGYAS+(gout.cascent()+TEXT_RAHAGYAS*4)*(i+1),szin,szin2,lista[i]) );
			}
			ObjKiemel(objektumok[2]);
			objektumok[objektumok.size()-1]->setter(cin);
		}

		bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
		void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
		void getter(ostream& ki) const;
};

bool KIVALASZTO::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
		{
			double ux,uy; // Kamera elmozdulás miatt kellenek.
			ux=x+X0;uy=y+Y0;
			kamera.getKamCoords(ux,uy);
			for (int i = objektumok.size()-1; i >= 2; i--)
			{
				if (objektumok[i]->BenneVan(ev.pos_x-ux,ev.pos_y-uy)) {
					objektumok[objektumok.size()-1]->setter(cin);
					objektumok[i]->setter(cin);
					ObjKiemel(objektumok[i]);
					return true;
				}
			}
			
		}
		else if (ev.button==btn_wheelup)
		{
			double ox,oy;
			objektumok[0]->getPosition(ox,oy); if (oy>0) return false;
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				objektumok[i]->getPosition(ox,oy);
				objektumok[i]->setPosition(ox,oy+(gout.cascent()+TEXT_RAHAGYAS*4));
			}
			return true;
		}
		else if (ev.button==btn_wheeldown)
		{
			double ox,oy;
			objektumok[1]->getPosition(ox,oy); 
			if (oy<sy) return false;
			for (int i = objektumok.size()-1; i >= 0; i--)
			{
				objektumok[i]->getPosition(ox,oy);
				objektumok[i]->setPosition(ox,oy-(gout.cascent()+TEXT_RAHAGYAS*4));
			}
			return true;
		}
	}
	return false; // Nem fogja el, (pl így el lehet húzni az alatta lévő ablakkal együtt.)
}

void KIVALASZTO::getter(ostream& ki) const 
{
	objektumok[2]->getter(ki);
};



#endif