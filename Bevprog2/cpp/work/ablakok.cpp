#include "env.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	long long int sid = 1;
	env.newSprite(sid,300,-50,300,160,170,160); sid++;

	gin.timer(20);

	long long int lenyomva = 0;
	double kx,ky = 0;

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		if (env.ev.type==ev_timer){
			env.kirajzol();
		} else
		if (env.ev.type==ev_mouse)
		{
			if (env.ev.button==btn_left)
				for (int i = 1; i < sid; ++i)
					if (env.SpriteBenneVan(i,env.ev.pos_x,env.ev.pos_y)) {
						env.getSpritePosition(i,kx,ky);
						kx-=env.ev.pos_x;
						ky-=env.ev.pos_y;
						lenyomva=i;
					}

			if (-env.ev.button==btn_left) {lenyomva=0; kx=0; ky=0;}

			if (env.ev.button==btn_right) {
				env.newSprite(sid,env.ev.pos_x,env.ev.pos_y,300,160,170,160); sid++;
			};

			if (lenyomva)
			{
				env.setSpritePosition(lenyomva,env.ev.pos_x+kx,env.ev.pos_y+ky);
			}
		}
		
	}
	return 0;
}
