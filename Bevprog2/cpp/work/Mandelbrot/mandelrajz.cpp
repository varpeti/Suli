#include "komplex.hpp"
#include "graphics.hpp"
#include <iostream>
#include <cmath>
using namespace genv;

double lex=0,ley=0,lzoom=2.0;


void mandelrajz(int XX, int YY, int MAX, double zoom=2.0,double ex=0.0,double ey=0.0) {
	std::cout << ex << " " << ey << std::endl;

	lex+=(XX/2-ex)*(lzoom*2/double(XX)); // Az előző nagyítás alapján kiszámolja hova hogyan tolja el.
	ley+=(YY/2-ey)*(lzoom*2/double(YY));
	lzoom=zoom;

	for (int x=0;x<XX;x++) {
		double cr = (zoom*2/double(XX))*x - zoom -lex;
		for (int y=0;y<YY;y++) {
			double ci = (zoom*2/double(YY))*y - zoom -ley;
			komplex c(cr, ci);
			komplex z(0,0);
			int t = 0;
			while (z.re()*z.re()+z.im()*z.im() < zoom*2 && t < MAX) {
				z = z*z+c;
				++t;
			}
			double rr,gg,bb;
			t*=15;
			if (t<=255) 				{rr=255-(t-0*255); 	gg=(t-0*255); 		bb=000;} 			else
			if (t>255 and t<=2*255) 	{rr=000; 			gg=255-(t-1*255); 	bb=(t-1*255);} 		else
			if (t>2*255) 				{rr=(t-2*255); 		gg=000; 			bb=255-(t-2*255);}
			rr=0;
			gout << move_to(x,y) << color(rr,gg,bb) << dot;
		}
		gout << refresh; // Ez csak azért van hogy lássam betöltődni
	}
}
