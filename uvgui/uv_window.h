//---------------------------------------------------------------------------
#ifndef _UV_WINDOW_H_
#define _UV_WINDOW_H_
//---------------------------------------------------------------------------
#include "uv_group.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_window
 *  @brief Erstellt ein Window, welches weitere Widgets enthalten kann.
 *  @author Lukas H
 *  @version 1.0
 *
 *  Ein einfaches Fenster
 */
//---------------------------------------------------------------------------
class uv_window:public uv_group
{
private:
    bool dragged;
public:
    uv_window( int mx, int mw, int width, int height,uv_group *parent, char * titel=0);
    void draw();
    void key_action(int key,int mod, int what);
    bool mouse_action(int x, int y, int key, int what);
    void mouse_move_rel(int rel_x, int rel_y);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

