#include "uv_gui.h"
//#include "sdl.h"
//Diese Source Datei beinhaltet einige Zeiger und globale Funktionen...



static uv_window *root_pointer;


void set_root_pointer(uv_window *ptr)
{
	root_pointer=ptr;
}

void run()
{ 
	SDL_Event event;
	while(SDL_PollEvent(&event)>=0)
	{
		switch(event.type)
      	{
         	case SDL_QUIT:
            	return;
            	break;
         	case SDL_KEYDOWN:
	    		if(event.key.keysym.sym == SDLK_ESCAPE)
            	{
               		return;
	       		
	    		}
            	break;
      	}
		root_pointer->draw();
	}

}
