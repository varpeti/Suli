#include "env.hpp"

using namespace genv;


int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	env.newsprite("1",100,0,300,160,170,160);
	env.newsprite("2",300,-50,300,160,170,160);
	env.newsprite("3",500,500,300,160,170,160);
	env.newsprite("4",0,200,420,340,190,140);
	env.newsprite("5",-50,400,420,340,190,140);
	env.newsprite("6",1200,400,420,340,190,140);
	gout << text("hello world");
	env.kirajzol();
	while(gin >> env.ev and env.ev.keycode!=key_escape) {
	}
	return 0;
}
