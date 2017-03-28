#include "graphics.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "mandelrajz.hpp"
#include "komplex.hpp"

#include "mandelrajz.cpp" // EZT NEM SZABAD SOHA

using namespace genv;
using namespace std;

const int XX=800;
const int YY=600;


const int MAX = 255;

double nagyitas = 2;

int main()
{
	gout.open(XX,YY);
	mandelrajz(XX,YY, MAX, nagyitas);
	event ev;
	while(gin >> ev && ev.keycode != key_escape) {
		if (ev.type==ev_mouse and ev.button==btn_left)
		{
			gout << color(000,000,000) 
				<< move_to(0,0) 
				<< box(XX,YY);
			nagyitas/=1;

			mandelrajz(XX,YY, MAX,nagyitas,ev.pos_x,ev.pos_y);
			
		}
	}
	return 0;
}

