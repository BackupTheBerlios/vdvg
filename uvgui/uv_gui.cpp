#include "uv_gui.h"
//#include "sdl.h"
//Diese Source Datei beinhaltet einige Zeiger und globale Funktionen...

#include <iostream>
using namespace std;

static int mouse_x;		//aktuelle Maus x- Koordinate
static int mouse_y;		//aktuelle Maus y- Koordinate

int get_mouse_x()
{
    return mouse_x;
}

int get_mouse_y()
{
    return mouse_y;
}

void set_mouse_x(int x)
{
    mouse_x=x;
}

void set_mouse_y(int y)
{
    mouse_y=y;
}
