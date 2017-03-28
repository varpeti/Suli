#include "graphics.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "mandelrajz.hpp"
#include "komplex.hpp"

using namespace genv;
using namespace std;

const int XX=800;
const int YY=600;


const int MAX = 255;

double nagyitas = 2;

int main()
{
	gout.open(XX,YY);

	//gin.timer(1000);

	mandelrajz(XX,YY, MAX, nagyitas, XX/2, YY/2); gout << refresh;
	//mandelrajz(XX,YY, MAX,nagyitas,XX*0.3994999999988,YY*0.195303); gout << refresh;

	event ev;
	while(gin >> ev && ev.keycode != key_escape) {
		if (ev.type==ev_mouse and ev.button==btn_left)
		{
			nagyitas/=1.1;

			mandelrajz(XX,YY, MAX,nagyitas,ev.pos_x,ev.pos_y);
			
		}
		if (ev.type==ev_timer)
		{
			nagyitas/=1.01;
			mandelrajz(XX,YY, MAX,nagyitas,XX/2,YY/2);
			gout << refresh;
		}

	}
	return 0;
}

