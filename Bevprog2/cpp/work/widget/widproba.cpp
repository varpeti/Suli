#include "env.hpp"
#include "ablak.hpp"
#include "stattext.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.kepek_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	OBJ *ablak = new ABLAK(300,0,500,300,0,170,160); env.addObj(ablak);
	OBJ *z = new ABLAK(10,10,400,200,0,SZIN(0,255,0)); ablak->addObj(z);
	OBJ *p = new ABLAK(10,10,300,150,0,SZIN(255,0,0)); z->addObj(p);
	OBJ *s = new ABLAK(10,10,250,100,0,SZIN(255,255,0)); z->addObj(s);
	OBJ *k = new ABLAK(10,10,10,10,0,SZIN(0,0,255)); p->addObj(k);
	OBJ *t = new STATTEXT(10,50,0,SZIN(0,0,0),SZIN(255,255,255),"Az almaspitet szeretem a legjobban, de a kortes is finom!"); s->addObj(t);

	gin.timer(20);

	bool lenyomva = false;
	double kx=0,ky=0;
	env.kamera.rset(0,150);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		env.UpdateDrawHandle();

		if (env.ev.type==ev_timer){
			//env.kamera.rset(1,1);
		} 
		else if (env.ev.type==ev_key)
		{
			ablak->setAllapot(255);
		}
		
	}

	return 0;
}
