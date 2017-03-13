#include "env.hpp"
#include "iostream"

using namespace genv;


int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	env.newSprite(100,0,300,160,170,160);
	env.newSprite(300,-50,300,160,170,160);
	env.newSprite(500,500,300,160,170,160);
	env.newSprite(0,200,420,340,190,140);
	env.newSprite(-50,400,420,340,190,140);
	env.newSprite(1200,200,300,210,200,150);

	gout << text("hello world"); // Nem fogja kiírni
	env.kirajzol();

	gin.timer(20);

	double forgat = 0.00;
	double kx,ky = 0;

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		if (env.ev.type==ev_timer){
			env.kamera.rset(kx,ky,1,forgat);
			env.kirajzol(); 
		} else
		if (env.ev.type==ev_mouse)
		{
			if (env.ev.button==btn_right) forgat=-0.01;
			else if (-env.ev.button==btn_right) forgat=0;
			if (env.ev.button==btn_left) forgat=0.01;
			else if (-env.ev.button==btn_left) forgat=0;

			int m = 50;
			int s = 5;
			if (env.ev.pos_x<m) kx=-s; 
			else if (env.ev.pos_x>1300-m) kx=s; 
			else kx=0;
			if (env.ev.pos_y<m) ky=-s; 
			else if (env.ev.pos_y>600-m) ky=s; 
			else ky=0;

			if (env.ev.button==btn_wheelup) env.kamera.rset(kx,ky,1/1.01,forgat);
			else if (env.ev.button==btn_wheeldown) env.kamera.rset(kx,ky,1.01,forgat);
		}
		if (env.ev.type==ev_key)
		{
			if (env.ev.keycode=='0') env.setSpriteAllapot(env.SPRITEOK[0],-1);
			else if (env.ev.keycode=='1') env.setSpritePosition(env.SPRITEOK[0],rand()%200-100,rand()%200-100);
			else if (env.ev.keycode=='2') env.setSpriteSebesseg(env.SPRITEOK[0],rand()%20-10,rand()%20-10);
			else if (env.ev.keycode=='3') env.setSpriteAllapot(env.utkozott(env.SPRITEOK[0]),-1);
			else if (env.ev.keycode=='4') env.newSprite(100,0,170,160,SZIN(rand()%255,rand()%255,rand()%255));
			else if (env.ev.keycode=='5') env.newSprite(300,-50,170,160,SZIN(rand()%255,rand()%255,rand()%255));
			else if (env.ev.keycode=='6') env.newSprite(500,500,300,160,170,160);
			else if (env.ev.keycode=='7') env.newSprite(0,200,420,340,190,140);
			else if (env.ev.keycode=='8') env.newSprite(-50,400,420,340,190,140);
			else if (env.ev.keycode=='9') env.newSprite(1200,200,300,210,200,150);
		}
		
	}
	return 0;
}
