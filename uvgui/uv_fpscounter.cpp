#include "uv_fpscounter.h"

uv_fpscounter::uv_fpscounter(uv_group *parent):uv_widget(parent->get_w()-100,0,50,20,parent,"")
{
	parent->add_child(this);
	counter.init("Test.ttf",12);
	counter.text << "Wait...";
}

void uv_fpscounter::draw()
{
	counter.print(get_absolute_x(),get_absolute_y());
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
}
