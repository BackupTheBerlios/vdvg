#include "uv_gui.h"
//#include "sdl.h"
//Diese Source Datei beinhaltet einige Zeiger und globale Funktionen...

#include <iostream>
using namespace std;

static uv_window *root_pointer;	//Das root windows
static int mouse_x;		//aktuelle Maus x- Koordinate
static int mouse_y;		//aktuelle Maus y- Koordinate

int get_mouse_x()
{
    return mouse_y;
}

int get_mouse_y()
{
    return mouse_x;
}

void set_root_pointer(uv_window * ptr)
{
    root_pointer = ptr;
}

void run()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) >= 0) {
        switch (event.type) {
        case SDL_QUIT:
            return;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return;
            }
            root_pointer->key_action((int)event.key.keysym.sym,(int)event.key.keysym.mod,(int)event.key.type);
            break;
        case SDL_MOUSEMOTION:	//uuh, mouse has moved...
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;
            break;

        }
        root_pointer->draw();
        SDL_GL_SwapBuffers();
    }

}
