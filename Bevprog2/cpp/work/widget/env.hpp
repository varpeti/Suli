//	Minden objektumban úlyabb objektumok lehetne. És mivel volt gyerekválalási tanácsdónál ezért különbőző típúsú objektumok lehetnek egymásba.
//	Az alobjektumok relatív koordinátával rendelkeznek, a "felettük" lévő bal felső sarka a (0,0) pont.
//
//		___OBJ[0]___________________ 		___OBJ[1]________________
//		|	___OBJ[0].OBJ[0]_____ 	|		|	___OBJ[1].OBJ[1]_	|
//		|	|					|	|		|	|				|	|
//		|	|OBJ[0].OBJ[0].OBJ_ |	|		|	|_______________|	|
//		|	||________________|	|	|		|	___OBJ[1].OBJ[2]_	|
//		|	|___________________|	|		|	|_______________|	|
//		|___________________________|		|_______________________|
//



#ifndef _ENV_	//ujabb definíció és fordítási hiba elkerülésére
#define _ENV_

#include "graphics.hpp"
#include "sstream"
#include "fstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "kamera.hpp"
#include "iostream"
#include "algorithm"

using namespace genv;
using namespace std;

/* OBJ-ektum class */ // ebből örőklődik minden

class OBJ // Az szülő
{
	public:
		double x,y; //x,y
		double sx,sy; //méret
		unsigned char allapot; // 255 törölhető, 0 látszik updetelődik, 1 lát, 2 update, else semmi
		vector<OBJ*> objektumok; // Pl ablakban lehetnek widgetek, de akár több ablak is, vagy egy legördülő widgetben több statikus szöveg widget.

		OBJ (double x,double y,double sx,double sy,unsigned char allapot) : x(x), y(y), sx(sx), sy(sy), allapot(allapot) {lenyomva=false; ex=0; ey=0;};
		virtual void srajzol(canvas &Tkepek, double X0, double Y0, double XX, double YY, KAMERA kamera) const =0;
		virtual void supdate(canvas &Tkepek, double X0, double Y0, KAMERA kamera, event ev);
		virtual bool shandle(event ev, double X0, double Y0);

		// Azért nem hülyeség a getter és setter mert SEXYBB mint a mezők :D | Egyébként az adatok főleg párosával vannak.
		void setPosition(double x,double y);
		void getPosition(double &x,double &y);
		void setAllapot(char allapot);
		unsigned char getAllapot();
		void setMeret(double sx,double sy);
		void getMeret(double &sx,double &sy);

		void ObjKiemel(OBJ *obj);
		bool BenneVan(double px, double py);

	private:
		bool lenyomva; // A tartalom mozgatáshoz kell.
		double ex,ey;
};

void OBJ::supdate(canvas &Tkepek, double X0, double Y0, KAMERA kamera, event ev)
{
	if (objektumok.size()==0) return;

	if (ev.type==ev_timer)
	{
		for (int i = 0; i < objektumok.size();) // Saját objektumai
		{
			if (objektumok[i]->allapot==0 or objektumok[i]->allapot==2) objektumok[i]->supdate(Tkepek,X0+x,Y0+y,kamera,ev);
			if (objektumok[i]->allapot==255)
			{ //törlés
				delete objektumok[i];
				objektumok[i] = objektumok[objektumok.size()-1];
				objektumok.pop_back();
			}
			else ++i; // Ha nem törlődik, a következőre lép
		}
	}
}

bool OBJ::shandle(event ev, double X0, double Y0)
{
	if (objektumok.size()==0) return false; // Ha nincs benne semmi.

	if (objektumok[objektumok.size()-1]->shandle(ev,X0+x,Y0+y)) return true; // Ha benne lévőt mozgattnak nem mozognak visszamenőleg.

	if (ev.type==ev_mouse)
	{
		if (ev.button==btn_left)
			for (int i = objektumok.size()-1; i >= 0; i--)
				if (objektumok[i]->BenneVan(ev.pos_x-(X0+x),ev.pos_y-(Y0+y))) 
				{
					objektumok[i]->getPosition(ex,ey);
					ex-=ev.pos_x;
					ey-=ev.pos_y;
					lenyomva=true;
					OBJ::ObjKiemel(objektumok[i]);
					break;
				}

		if (-ev.button==btn_left) {lenyomva=false; ex=0; ey=0;} // Ha felengedi

		if (lenyomva) objektumok[objektumok.size()-1]->setPosition(ev.pos_x+ex,ev.pos_y+ey); // ameddig nyomva mozog.
	}
	return lenyomva;
}

void OBJ::ObjKiemel(OBJ *obj)
{
	for (int i = 0; i < objektumok.size(); ++i)
		if (objektumok[i]==obj)
		{
			objektumok.push_back(obj);
			objektumok.erase(objektumok.begin()+i);
			return;
		}
}

void OBJ::setPosition(double ux,double uy)
{
	x=ux;
	y=uy;
}

void OBJ::getPosition(double &ux,double &uy)
{
	ux=x;
	uy=y;
}

void OBJ::setAllapot(char uallapot)
{
	if (uallapot>3 or uallapot<0 or uallapot!=255) return;
	allapot=uallapot;
}

unsigned char OBJ::getAllapot()
{
	return allapot;
}

void OBJ::setMeret(double usx,double usy)
{
	sx=usx;
	sy=usy;
}

void OBJ::getMeret(double &usx,double &usy)
{
	usx=sx;
	usy=sy;
}

bool OBJ::BenneVan(double px, double py)
{
	if (px>=x and px<=x+sx and py>=y and py<=y+sy) return true;
	return false;
};


/* CLASS 	*/

class ENV
{
	public:

	canvas Tkepek;	//az összes OBJ képét ide olvasom be

	unsigned int XX;
	unsigned int YY;

	// mezők;
	event ev;
	KAMERA kamera;

	//konst dest
	ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo);
	ENV(unsigned int szelesseg, unsigned int magassag);
	~ENV();

	// tagfüggvények
	void UpdateDrawHandle();
	bool kepek_beolvas(const char *fname); // BMP-ből olvassa be az összes képet

	vector<OBJ*> objektumok; // Az összes obj

	void ObjKiemel(OBJ *obj); // Előre hozza az objektumot
};

/* MEGVALÓSÍTÁS */

//konst

ENV::ENV(unsigned int szelesseg, unsigned int magassag, bool teljeskepernyo)
{
	srand(time(NULL));
	YY=magassag;
	XX=szelesseg;
	gout.open(XX,YY,teljeskepernyo);
}

ENV::ENV(unsigned int szelesseg, unsigned int magassag)
{
	srand(time(NULL));
	YY=magassag;
	XX=szelesseg;
	gout.open(XX,YY);
}

ENV::~ENV() //dest
{

}

void ENV::ObjKiemel(OBJ *obj)
{
	for (int i = 0; i < objektumok.size(); ++i)
		if (objektumok[i]==obj)
		{
			objektumok.push_back(obj);
			objektumok.erase(objektumok.begin()+i);
			return;
		}
}

void ENV::UpdateDrawHandle()
{

	if (objektumok.size()<1) return;

	static bool lenyomva=false; 
	static double ex=0,ey=0;

	if (ev.type==ev_timer)
	{
		gout << color(0,0,0) << move_to(0,0) << box(XX,YY);

		for (int i = 0; i < objektumok.size();) // Saját objektumai
		{
			if (objektumok[i]->allapot==0 or objektumok[i]->allapot==1) objektumok[i]->srajzol(Tkepek,0,0,XX,YY,kamera); // saját mérete a benne lévők korlátja
			if (objektumok[i]->allapot==0 or objektumok[i]->allapot==2) objektumok[i]->supdate(Tkepek,0,0,kamera,ev);
			if (objektumok[i]->allapot==255)
			{ //törlés
				delete objektumok[i];
				objektumok[i] = objektumok[objektumok.size()-1];
				objektumok.pop_back();
			}
			else ++i; // Ha nem törlődik, a következőre lép
		}

		gout << refresh;

	}else if (ev.type==ev_mouse and objektumok.size()!=0 and !objektumok[objektumok.size()-1]->shandle(ev,0,0)) // A legfelső (fókuszban lévő) megkapja az inputokat.
	{
		if (ev.button==btn_left)
			for (int i = objektumok.size()-1; i >= 0; i--)
				if (objektumok[i]->BenneVan(ev.pos_x,ev.pos_y)) 
				{
					objektumok[i]->getPosition(ex,ey);
					ex-=ev.pos_x;
					ey-=ev.pos_y;
					lenyomva=true;
					ENV::ObjKiemel(objektumok[i]);
					break;
				}

		if (-ev.button==btn_left) {lenyomva=false; ex=0; ey=0;}

		if (lenyomva) objektumok[objektumok.size()-1]->setPosition(ev.pos_x+ex,ev.pos_y+ey);
	}
}

bool ENV::kepek_beolvas(const char *fname) // CSAK azért is BMPből.
{
	FILE* f = fopen(fname, "rb"); if (!f) return false;
	char info[54] = {0}; // 54 byte: az infók
	fread(info, sizeof(char), 54, f); 

	unsigned int width = *(int*)&info[18]; //18. szélesség
	unsigned int height = *(int*)&info[22]; //22. magasság

	unsigned int size = 3 * width * height; // 3 byte pixelenként
	char* data = new char[size]; // lefoglalás
	fread(data, sizeof(char), size, f); // beolvasás egyszerre / csak ha nincsenek színtérinformációk, különben csúszik
	fclose(f);

	Tkepek.open(width,height); // canvas megnyitása
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) //y
	{
		for (unsigned int j = 0; j < width; j++) //x
		{
			unsigned int bb = data[k]; k++; // Igen a mikrofos BBGGRR formátumot használ
			unsigned int gg = data[k]; k++;
			unsigned int rr = data[k]; k++;
			Tkepek << move_to(j,height-i) << color(rr,gg,bb) << dot; // ja és fejjel lefele (MIÉRT???)
		}
	}
	delete data; //Nem használt memória felszabadítása
	return true;
}

#endif