#include "../graphics.hpp"
#include "env.hpp"


using namespace genv;

int main()
{
    ENV(200,200);
    gout << text("hello world") << refresh;
    event ev;
    while(gin >> ev and ev.keycode!=key_escape) {
    }
    return 0;
}
