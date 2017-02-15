//CODEIMGAME
#include "../graphics.hpp"
#include "sstream"
#include "vector"

using namespace genv;
using namespace std;

struct Sboxok
{
	int x;
	int y;
	int vx;
	int vy;
	int rr,gg,bb;
	int elet;
};

int main()
{
	gout.open(1330,600,true);

	std::vector<Sboxok> v;

	gin.timer(100);

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type=ev_timer) {

			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box_to(1329,599);

			for (Sboxok b:v)
			{
				gout << color(b.rr,b.gg,b.bb)
					<< move_to(b.x,b.y)
					<< box(10,10);

				b.x+=b.vx;
				b.y+=b.vy;
				b.vy--;
				b.elet--;
			}

			gout << refresh;

			//időzítő
			gin.timer(100);
		}

		if (ev.type=ev_mouse)
		{
			Sboxok b;
			b.x = ev.pos_x;
			b.y = ev.pos_y;
			b.vx=0;
			b.vy=3;
			b.elet = 100;
			b.rr=255;
			b.gg=255;
			b.bb=000;
			v.push_back(b);
		}
	}
	return 0;
}
