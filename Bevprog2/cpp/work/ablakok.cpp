#include "env.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	env.newSprite(300,-50,300,160,170,160);

	gin.timer(20);

	int lenyomva = -1;
	double kx,ky = 0;

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		if (env.ev.type==ev_timer){
			env.kirajzol();
		} else
		if (env.ev.type==ev_mouse)
		{
			if (env.ev.button==btn_left)
				for (int i = 0; i < env.SPRITEOK.size(); ++i)
					if (env.SpriteBenneVan(env.SPRITEOK[i],env.ev.pos_x,env.ev.pos_y)) {
						env.getSpritePosition(env.SPRITEOK[i],kx,ky);
						kx-=env.ev.pos_x;
						ky-=env.ev.pos_y;
						lenyomva=i;
					}

			if (-env.ev.button==btn_left) {lenyomva=-1; kx=0; ky=0;}

			if (env.ev.button==btn_right) {
				env.newSprite(env.ev.pos_x,env.ev.pos_y,170,160,SZIN(rand()%255,rand()%255,rand()%255));
			};

			if (env.ev.button==btn_wheelup) 
				for (int i = env.SPRITEOK.size()-1; i >= 0; i--)
					if (env.SpriteBenneVan(env.SPRITEOK[i],env.ev.pos_x,env.ev.pos_y)) {
						env.getSpritePosition(env.SPRITEOK[i],kx,ky);
						kx-=env.ev.pos_x;
						ky-=env.ev.pos_y;
						env.setSpriteSzam(env.SPRITEOK[i],1); break;
					}
			if (env.ev.button==btn_wheeldown)
				for (int i = env.SPRITEOK.size()-1; i >= 0; i--)
					if (env.SpriteBenneVan(env.SPRITEOK[i],env.ev.pos_x,env.ev.pos_y)) {
						env.getSpritePosition(env.SPRITEOK[i],kx,ky);
						kx-=env.ev.pos_x;
						ky-=env.ev.pos_y;
						env.setSpriteSzam(env.SPRITEOK[i],-1); break;
					}

			if (lenyomva!=-1)
			{
				env.setSpritePosition(env.SPRITEOK[lenyomva],env.ev.pos_x+kx,env.ev.pos_y+ky);
			}
		}
		
	}
	return 0;
}
