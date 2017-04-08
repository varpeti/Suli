#include "env.hpp"
#include "ablak.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.kepek_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	OBJ *ablak = new ABLAK(300,0,300,160,0,170,160); env.objektumok.push_back(ablak);
	OBJ *a = new ABLAK(10,10,100,80,0,SZIN(0,255,0)); env.objektumok[0]->objektumok.push_back(a);
	a = new ABLAK(10,10,60,50,0,SZIN(255,0,0)); env.objektumok[0]->objektumok[0]->objektumok.push_back(a);
	a = new ABLAK(10,10,50,60,0,SZIN(255,255,0)); env.objektumok[0]->objektumok[0]->objektumok.push_back(a);
	a = new ABLAK(10,10,10,10,0,SZIN(0,0,255)); env.objektumok[0]->objektumok[0]->objektumok[0]->objektumok.push_back(a);

	gin.timer(20);

	bool lenyomva = false;
	double kx=0,ky=0;

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		env.UpdateDrawHandle();

		if (env.ev.type==ev_timer){
			
		} 
		else if (env.ev.type==ev_mouse)
		{

		}
		
	}
	return 0;
}
