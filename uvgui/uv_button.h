//---------------------------------------------------------------------------
// File:       uv_button.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_BUTTON_
#define _UV_BUTTON_

//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include <SDL.h>
#include <SDL_opengl.h>


/*! @class uv_button
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
class uv_button: public uv_group
{
private:
    uv_text text;
public:
    uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel=0);
    void draw();
    bool mouse_action(int x, int y, int button, int what);
    void key_action(int key, int sym, int mod, int what);
};

#endif
