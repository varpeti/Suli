#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "time.h"
#include "math.h"
#include "iostream"

#define PI 3.141592

using namespace genv;
using namespace std;

const int XX = 1330;
const int YY = 600;
const bool teljes = false;

struct Skoordinatak
{
	double x;
	double y;

	Skoordinatak (double ux, double uy) 
	{
		x=ux;
		y=uy;
	};

	Skoordinatak () 
	{};

	double operator|(Skoordinatak jobb)
	{
	return sqrt( (x-jobb.x)*(x-jobb.x)+(y-jobb.y)*(y-jobb.y) );
	}

};

void kor(Skoordinatak pozicio, double sugar)
{
	for (int y = -sugar; y <=sugar; ++y)
	{
		for (int x = -sugar; x <=sugar; ++x)
		{
			if (x*x+y*y-sugar*sugar<1) gout << move_to(x+pozicio.x,y+pozicio.y) << dot;
		}
	}
}

bool ukozott(Skoordinatak A,Skoordinatak B, double sugarA, double sugarB)
{
	return (A|B)<=sugarA+sugarB and (A|B)>0;
}

struct Sgolyo
{
	private:
	double sugar;
	Skoordinatak pozicio;
	Skoordinatak sebesseg;
	unsigned char R,G,B;

	public:
	Sgolyo (double usugar, Skoordinatak upozicio, Skoordinatak usebesseg) 
	{
		sugar = usugar;
		pozicio = upozicio;
		sebesseg = usebesseg;
		R = rand()%255;
		G = rand()%255;
		B = rand()%255;
	};

	void rajzol()
	{
		gout << color(R,G,B);
		kor(pozicio,sugar);
	}

	void update(vector<Sgolyo> &labdak)
	{
		for (int i = 0; i < labdak.size(); ++i)
		{
			if (ukozott(pozicio,labdak[i].pozicio,sugar,labdak[i].sugar)) {
				cout << "a" << endl;
				double alpha = atan((pozicio.y - labdak[i].pozicio.y) / (pozicio.x - labdak[i].pozicio.x));
				double X1 = sebesseg.x * cos(-alpha) - sebesseg.y * sin(-alpha);
				double Y1 = sebesseg.x * sin(-alpha) + sebesseg.y * cos(-alpha);
				double X2 = labdak[i].sebesseg.x * cos(-alpha) - labdak[i].sebesseg.y * sin(-alpha);
				double Y2 = labdak[i].sebesseg.x * sin(-alpha) + labdak[i].sebesseg.y * cos(-alpha);

				double newX1 = X2 * cos(alpha) - Y1 * sin(alpha);
				double newY1 = X2 * sin(alpha) + Y1 * cos(alpha);
				double newX2 = X1 * cos(alpha) - Y2 * sin(alpha);
				double newY2 = X1 * sin(alpha) + Y2 * cos(alpha);

				sebesseg.x = newX1;
				sebesseg.y = newY1;
				labdak[i].sebesseg.x = newX2;
				labdak[i].sebesseg.y = newY2;
			}
		} 

		pozicio.x+=sebesseg.x;
		pozicio.y+=sebesseg.y;

		if (pozicio.x-sugar<0) {
			sebesseg.x=-sebesseg.x;
			pozicio.x=0+sugar;
		}
		if (pozicio.x+sugar>XX){
			sebesseg.x=-sebesseg.x;
			pozicio.x=XX-sugar;
		}
		if (pozicio.y-sugar<0) {
			sebesseg.y=-sebesseg.y;
			pozicio.y=0+sugar;
		}
		if (pozicio.y+sugar>YY){
			sebesseg.y=-sebesseg.y;
			pozicio.y=YY-sugar;
		}
	}
};


int main()
{
	srand (time(NULL));

	gout.open(XX,YY,teljes);

	gin.timer(20);

	vector<Sgolyo> labdak;

	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
		if (ev.type==ev_timer) 
		{
			gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
			for (int i = 0; i < labdak.size(); ++i)
			{
				labdak[i].update(labdak);
				labdak[i].rajzol();
			}
			gout << refresh;
		}
		else if (ev.type==ev_mouse)
		{
			if (ev.button==btn_left) {
				Sgolyo labda(rand()%20+3,Skoordinatak(ev.pos_x,ev.pos_y),Skoordinatak((rand()%600-300)/100.0,(rand()%600-300)/100.0));
				labdak.push_back(labda);
			}
		}
		else if (ev.type==ev_key)
		{
			
		}
	}
	return 0;
}