#ifndef _SZAMBOX_	//ujabb definíció és fordítási hiba elkerülésére
#define _SZAMBOX_

#include "textbox.hpp"

class SZAMBOX : public TEXTBOX
{
	protected:

	double A; // Határértékei
	double B;
	double szam;

	public:

	SZAMBOX(double x, double y, double A, double B, SZIN szin, SZIN szin2, string szoveg="0")
		: TEXTBOX(x,y,10,szin,szin2,szoveg)
	{
		sx=gout.twidth("0")*10+TEXT_RAHAGYAS;
	}

	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
	virtual void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
	void hozzaad(double x);
};

bool SZAMBOX::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_key)
	{
		if ( (ev.keycode>=48 and ev.keycode<=57) or ev.keycode==43 or ev.keycode==45 or ev.keycode==46 or ev.keycode==101) szoveg+=ev.keycode; // 0123456789+-.e
		else if (ev.keycode==key_backspace) szoveg = szoveg.substr(0, szoveg.size()-1); // Törlés
		else if (ev.keycode==key_enter) {ostringstream strs; strs << szam; szoveg = strs.str();}

		if (szoveg.size()>size) szoveg = szoveg.substr(0, szoveg.size()-1); // Nincs több karakter hely
		szam = atof(szoveg.c_str()); cout << szam << endl;
		return true; // Elfogja a karaktereket.
	}
	return false;
}

void SZAMBOX::hozzaad(double x)
{
	szam+=x;
}

#endif