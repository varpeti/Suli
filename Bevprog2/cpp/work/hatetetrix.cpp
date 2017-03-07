#include "env.hpp"
#include "iostream"

using namespace genv;

#define Ksz 1230
#define Km 	400

/*			
	1:	2:	3:	4:	5:	6:	7:
135	0	00			0		0		
180	0	0	0	00	00	 0	00	
225	0	0	0	00	 0	00	0	
270	0		00			0
*/

struct Sdata
{
	double x;
	double y;

	Sdata(double ux, double uy)
	{
		x=ux;
		y=uy;
	}
};

struct Selemek
{	
	long long int id;
	int kep;
	char tipus;
	vector<Sdata> data;
	Selemek(ENV &env,char utipus,int ukep,long long int &ids)
	{
		id = ids+4;
		kep = ukep;
		tipus = utipus;

		switch (tipus) { //ez így néz ki jól. Nem kell ciklus :D
			case 1 : {
				Sdata a0(-90,135);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-90,270);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 2 : {
				Sdata a0(-90,135);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-45,135);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 3 : {
				Sdata a0(-45,270);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-90,270);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 4 : {
				Sdata a0(-45,180);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-45,225);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 5 : {
				Sdata a0(-90,135);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-45,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-45,180);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 6 : {
				Sdata a0(-45,225);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-45,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-90,270);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
			case 7 : {
				Sdata a0(-90,135);	env.newSprite(ids,a0.x,a0.y,kep,0,45,45); ids++; data.push_back(a0);
				Sdata a1(-90,180);	env.newSprite(ids,a1.x,a1.y,kep,0,45,45); ids++; data.push_back(a1);
				Sdata a2(-90,225);	env.newSprite(ids,a2.x,a2.y,kep,0,45,45); ids++; data.push_back(a2);
				Sdata a3(-45,180);	env.newSprite(ids,a3.x,a3.y,kep,0,45,45); ids++; data.push_back(a3);
				break;}
		}
		for (int i = 1; i <= 4; ++i)
		{
			if (!env.setSpriteSebesseg(id-i,5,0)) cout << "gond: " << i << endl;
		}
	}
};


int main()
{

	ENV env (Ksz,Km,false);
	if(!env.spriteok_beolvas("star.bmp")) cout << "Nem talalhato a kep!";
           
	env.newSprite(-1,-90,-10,0,0,Ksz,10); env.setSpriteAllapot(-1,0);	// verem jobboldala  -----------|
	env.newSprite(-2,Ksz,-10,0,0,10,Km+10); env.setSpriteAllapot(-2,0);// verem alja 					|
	env.newSprite(-3,-90,Km,0,0,Ksz,10); env.setSpriteAllapot(-3,0);	// verem jobboldala  -----------|

	long long int ids=1; // nem lehet 0
	std::vector<Selemek> elemek;

	gin.timer(33);

	env.kamera.aset(20,-20);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {
		
		if (env.ev.type==ev_timer) 
		{
			for (std::vector<Selemek>::iterator i = elemek.begin(); i != elemek.end(); ++i)
			{
				for (int j = 1; j <= 4; ++j){
					long long int b = env.utkozott(i->id-j);
					if (b>0) { if (env.setSpriteAllapot(b,255)) cout << "tr: " << b << " " << i->id-j << endl;
					}
				}
			}
			env.kirajzol();
		}
		else if (env.ev.type==ev_key)
		{
			Selemek elem(env,rand()%6+1,rand()%5*45,ids); elemek.push_back(elem);
		}
	}
	int a;
	//cin >> a; //debug
	return 0;
}
