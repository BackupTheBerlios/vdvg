//---------------------------------------------------------------------------
// File:       uv_window.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_window.h"
//---------------------------------------------------------------------------
uv_window::uv_window(int mx, int my, int width, int height,
                     uv_group *parent, char *label)
                     :uv_group(mx, my, width, height, parent, label, true)
                      , oben(0, 0, get_w(), 20, this, "Test.bmp")
{
    dragged = 0;

    //Display-Listen Zeugs:
    if(!(stranslation = glGenLists(3)))
       return; //Error !!
    drawing = stranslation+1;
    etranslation = drawing+1;

    redraw = true;
    retranslate = true;
};
//---------------------------------------------------------------------------
void uv_window::draw(basic_string<GLuint> * clist)
{
    if(!get_visible()) return;

    if(retranslate)
    {
       glNewList(stranslation, GL_COMPILE);
       glTranslatef(get_absolute_x(), get_absolute_y(), 0);
       glEndList();

       glNewList(etranslation, GL_COMPILE);
       glTranslatef(-1*get_absolute_x(), -1*get_absolute_y(), 0);
       glEndList();

       retranslate = false;
    }

    if(redraw)
    {
       //Eigenes Fenster zeichnen...
       glNewList(drawing, GL_COMPILE);

       glBegin (GL_QUADS);
       //glColor3ub (0, 0, 255);
       glColor4ub(0, 0, 255, 100);
       glVertex2i (0, 0);
       glVertex2i (get_w (), 0);
       glVertex2i (get_w (), get_h ());
       glVertex2i (0, get_h ());

       //glColor3ub (200, 200, 0);
       glColor4ub(200, 200, 0, 100);
       glVertex2i (2, 20);
       glVertex2i (get_w()-2, 20);
       glVertex2i (get_w()-2, get_h()-2);
       glVertex2i (2, get_h()-2);
       glEnd ();

       glEndList();
       redraw = false;
    }

    clist->push_back(stranslation);
    clist->push_back(drawing);

    //Alle Childs zeichnen
    draw_childs(clist);

    clist->push_back(etranslation);
};
//---------------------------------------------------------------------------
bool uv_window::mouse_action(int x, int y, int button, int what)
{
    if(y < 20 && what==SDL_MOUSEBUTTONDOWN)
        dragged=true; //Mausklick im Drag Bereich
    if(what==SDL_MOUSEBUTTONUP)
        dragged=false;

    return mouse_action_childs(x, y, button, what);
};
//---------------------------------------------------------------------------
void uv_window::key_action(int key, int sym, int mod, int what)
{
    key_action_childs(key, sym, mod, what);
};
//---------------------------------------------------------------------------
void uv_window::mouse_move_rel(int rel_x, int rel_y)
{
    if(dragged)
    {
        set_pos(get_x()+rel_x,get_y()+rel_y);
        retranslate = true;
    }

    mouse_move_rel_childs(rel_x, rel_y);
};
//---------------------------------------------------------------------------

