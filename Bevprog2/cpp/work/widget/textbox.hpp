#ifndef _TEXTBOX_	//ujabb definíció és fordítási hiba elkerülésére
#define _TEXTBOX_

#include "stattext.hpp"

class TEXTBOX : public STATTEXT
{
	protected:

	unsigned int size;

	public:

	TEXTBOX(double x, double y, unsigned int size, SZIN szin, SZIN szin2, string szoveg="")
		: STATTEXT(x,y,szin,szin2,szoveg), size(size)
	{
		sx=gout.twidth("A")*size+TEXT_RAHAGYAS;
	}

	virtual bool supdate(event ev, double X0, double Y0, KAMERA kamera); 
	virtual void addObj(OBJ *obj) {}; // Nem lehet hozzáadni újabb objektumokoat.
};

bool TEXTBOX::supdate(event ev, double X0, double Y0, KAMERA kamera)
{
	if (ev.type==ev_key)
	{
		if (ev.keycode>31) szoveg+=ev.keycode; // Írás
		else if (ev.keycode==key_backspace) szoveg = szoveg.substr(0, szoveg.size()-1); // Törlés

		if (szoveg.size()>size) szoveg = szoveg.substr(0, szoveg.size()-1); // Nincs több karakter hely
		return true; // Elfogja a karaktereket.
	}
	return false;
}

#endif