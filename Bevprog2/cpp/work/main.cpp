//#include "../graphics.hpp"
#include "env.hpp"

using namespace genv;


int main()
{
	ENV env (0,0,1200,600,false);
	//env.newsprite(100,100);
	//env.newsprite(100,200);
	gout << text("hello world") << refresh;
	env.kirajzol();
	while(gin >> env.ev and env.ev.keycode!=key_escape) {
	}
	return 0;
}
