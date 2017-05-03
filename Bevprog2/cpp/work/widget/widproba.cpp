#include "env.hpp"
#include "ablak.hpp"
#include "stattext.hpp"
#include "textbox.hpp"
#include "szambox.hpp"
#include "szambeallito.hpp"
#include "kivalaszto.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.kepek_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	OBJ *ablak = new ABLAK(300,0,600,550,170,30); env.addObj(ablak);
	OBJ *z = new ABLAK(10,10,500,300,SZIN(0,255,0)); ablak->addObj(z);
	OBJ *p = new ABLAK(10,10,300,150,SZIN(255,0,0)); z->addObj(p);
	OBJ *s = new ABLAK(10,10,250,100,SZIN(255,255,0)); z->addObj(s);
	OBJ *k = new ABLAK(50,50,10,10,SZIN(0,0,255)); p->addObj(k);
	OBJ *t = new STATTEXT(10,50,SZIN(0,0,0),SZIN(255,255,255),"Az almaspitet szeretem a legjobban, de a kortes is finom!"); s->addObj(t);
	OBJ *tb = new TEXTBOX(10,10,10,SZIN(0,0,0),SZIN(255,255,255)); s->addObj(tb);
	OBJ *szam = new SZAMBOX(10,10,-3.1415e6,900,SZIN(0,0,0),SZIN(255,255,255),-9e99,11); p->addObj(szam);
	OBJ *szam2 = new SZAMBEALLITO(10,10,-100,100,SZIN(200,150,100),SZIN(0,0,0)); env.addObj(szam2);
	OBJ *szam3 = new SZAMBEALLITO(10,110,-100,100,1,1,100,100,SZIN(0,0,0),SZIN(0,255,0)); env.addObj(szam3);

	vector<string> lista; lista.push_back("almaspite");lista.push_back("barack");lista.push_back("citrom");lista.push_back("dinnye");lista.push_back("1");lista.push_back("26435");lista.push_back("szilva");
	OBJ *leg = new KIVALASZTO(10,110,SZIN(0,0,0),SZIN(255,255,255),lista,5); ablak->addObj(leg);

	OBJ *form = new ABLAK(100,100,500,400,SZIN(200,100,100)); env.addObj(form);
	OBJ *gomb = new ABLAK(10,55,10,10,SZIN(0,0,255),false); form->addObj(gomb);
	OBJ *gomb2 = new ABLAK(155,55,10,10,SZIN(255,0,0),false); form->addObj(gomb2);
	OBJ *ftb = new TEXTBOX(50,50,10,SZIN(0,0,0),SZIN(255,255,255)); form->addObj(ftb);
	OBJ *list = new KIVALASZTO(10,110,SZIN(0,0,0),SZIN(255,255,255),lista,2); form->addObj(list);

	gin.timer(20);

	bool lenyomva = false;
	double kx=0,ky=0;
	//env.kamera.rset(0,150);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		
		if (env.ev.type==ev_timer){
			//env.kamera.rset(1,1);
		} 
		else if (env.ev.type==ev_key)
		{
			if (env.ev.keycode=='j') {
				stringstream str ("alma");
				leg->setter(str);
			}
			if (env.ev.keycode=='a') {
				list->getter(cout); cout << endl;
			}
		}

		env.UpdateDrawHandle();

		stringstream a,b,c;
		form->getter(a);
		b << gomb;
		c << gomb2;
		if (a.str()==b.str()) {
			a.str("");
			ftb->getter(a);
			list->setter(a); // Hozzáadás
			form->ObjKiemel(list);
		}else if (a.str()==c.str()){
			a.str("");
			list->setter(a); // törlés
			form->ObjKiemel(list);
		}

		
	}

	return 0;
}
