//---------------------------------------------------------------------------
// File:       uv_fpscounter.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#include "uv_fpscounter.h"

uv_fpscounter::uv_fpscounter(uv_group *parent)
                             : uv_group(parent->get_w()-100,0,50,20,parent,""),
                               counter(0, 0, 0, 0, this, "Framecounter")
{
	counter.set_pos(0,0);
	counter.set_color(0xff,0xff,0xff);
	counter.init("Test.ttf",16);
	//counter.text2 << "Wait...";
        counter.pushtext("Wait...");
        //counter.text("Wait...");
}

void uv_fpscounter::draw()
{
	static int frames=0;
	static long tickdiff=0;
	if( (SDL_GetTicks() - tickdiff) > 1000)
	{
		//counter.text2.str("");
		//counter.text2 << "FPS: "<< frames;
                counter.pushtext("");
                string a; // = frames;
                string b = "FPS: ";
                string c = b + a;
                counter.pushtext(c);
		tickdiff = SDL_GetTicks();
		frames=0;
	}
	frames++;
	draw_childs();
}
