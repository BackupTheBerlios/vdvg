#ifndef _UV_MAINWINDOW_
#define _UV_MAINWINDOW_

#include "uv_group.h"

#include <SDL.h>
#include <SDL_opengl.h>
/*! @class uv_mainwindow
 *  @brief Erstellt das Main Window (SDL + OGL)
 *  @author Lukas H
 *  @version 1.0
 *
 *  Verwaltet alle anderen Widgets
 */

class uv_mainwindow:public uv_group
{
private:
    void init_SDL(int breite = 1024, int hoehe = 768, bool fullscreen=1, int bit = 32, int depth_size = 24, int stencil_size = 24, int doublebuffer = 1, int noframe = 0, char *label = 0);
public:
    uv_mainwindow( int width, int height, bool fullscreen=1, char * titel=0);
    void draw();
    void key_action(int key,int mod, int what);
    void mouse_action(int x, int y, int key, int what);
    void mouse_move_rel(int rel_x, int rel_y);
    void run();
};


#endif
