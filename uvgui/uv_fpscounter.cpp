#include "uv_fpscounter.h"

uv_fpscounter::uv_fpscounter(uv_group *parent):uv_group(parent->get_w()-100,0,50,20,parent,"")
{

	counter.set_parent(this);
	counter.set_pos(0,0);
	counter.set_color(0xff,0xff,0xff);
	counter.init("Test.ttf",12);
	counter.text << "Wait...";
}

void uv_fpscounter::draw()
{
	static int frames=0;
	static long tickdiff=0;
	if( (SDL_GetTicks() - tickdiff) > 1000)
	{
		counter.text.str("");
		counter.text << "FPS: "<< frames;
		tickdiff = SDL_GetTicks();
		frames=0;		
	}
	frames++;
	draw_childs();
}
