//#include "../graphics.hpp"
#include "env.hpp"

using namespace genv;


int main()
{
	ENV env (1400,800,1200,600,false);
	env.newsprite(100,100);
	gout << text("hello world") << refresh;
	event ev;
	while(gin >> ev and ev.keycode!=key_escape) {
	}
	return 0;
}
