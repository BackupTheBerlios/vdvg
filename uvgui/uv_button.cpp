//---------------------------------------------------------------------------
// File:       uv_button.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#include "uv_button.h"

uv_button::uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel)
                     :uv_group(mx,my,mw,mh,parent,mlabel), text(0, 0, 0, 0, this, "")
{
    text.init("Test.ttf",25);
    text.set_color(0xff,0x88,0x00);

    static string test = mlabel;
    test = mlabel;

    text.pushtext(test);

    //Den Text auf dem Button zentrieren
    text.set_pos((get_w()-text.get_width())/2, (get_h()-text.get_height())/2);
}

void uv_button::draw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    if(get_visible())
    {
        glBegin (GL_QUADS);
        // Links Oben
        if( mouse_over() ) glColor3ub (150, 150, 150);
        else glColor3ub (100, 100, 100);
        //glColor3ub(255, 0, 0);
        glVertex2i (get_absolute_x(), get_absolute_y());
        // Rechts Oben
        //glColor3ub (0, 255, 0);
        glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
        // Rechts Unten
        glColor3ub (255, 255, 255);
        //glColor3ub(255, 0, 0);

        glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
        // Links Unten
        //glColor3ub (255, 255, 0);
        glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
        glEnd ();

        draw_childs();
    }
}

bool uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        do_callback();
    }
	uv_widget::mouse_action(x,y,button,what);
    return true;
}

void uv_button::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
      do_callback();
}
