#include "komplex.hpp"
#include "graphics.hpp"
#include <iostream>
using namespace genv;

double elx=0,ely=0;


void mandelrajz(int XX, int YY, int MAX, double zoom=2.0,double ex=0.0,double ey=0.0) {
    std::cout << ex << " " << ey << std::endl;

    elx=0;
    ely=0;

    for (int x=0;x<XX;x++) {
        for (int y=0;y<YY;y++) {
            double cr = (zoom*2/double(XX))*x - zoom;
            double ci = (zoom*2/double(YY))*y - zoom;
            komplex c(cr, ci);
            komplex z(0,0);
            int t = 0;
            while (z.re()*z.re()+z.im()*z.im() < 4.0 && t < MAX) {
                z = z*z+c;
                ++t;
            }
            t=t*15;
            gout << move_to(x,y) << color(t,t,t) << dot;
        }
        gout << refresh; // Ez csak azért van hogy lássam betöltődni
    }
}
