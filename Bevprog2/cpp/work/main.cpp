#include "env.hpp"
#include "iostream"

using namespace genv;

void gutkozott(long long int aid, double &ax, double &ay, unsigned int &asx, unsigned int &asy, double &avx, double &avy,long long int bid, double &bx, double &by, unsigned int &bsx, unsigned int &bsy, double &bvx, double &bvy)
{};


int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	env.newSprite(1,100,0,300,160,170,160);
	env.newSprite(2,300,-50,300,160,170,160);
	env.newSprite(3,500,500,300,160,170,160);
	env.newSprite(4,0,200,420,340,190,140);
	env.newSprite(5,-50,400,420,340,190,140);
	env.newSprite(6,1200,200,300,210,200,150);
	gout << text("hello world");
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
		
	}
	return 0;
}
