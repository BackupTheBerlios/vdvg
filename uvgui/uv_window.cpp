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
                      , oben(5, 0, get_w()-10, 20, this, "windowdesign.tga")
                      , obenl(0, 0, 5, 20, this, "windowdesign.tga")
                      , obenr(get_w()-5, 0, 5, 20, this, "windowdesign.tga")
                      , but1(get_w()-21, 0, 16, 20, this, "windowdesign.tga")
                      , but2(get_w()-37, 0, 16, 20, this, "windowdesign.tga")
                      , but3(get_w()-53, 0, 16, 20, this, "windowdesign.tga")
                      , but4(get_w()-69, 0, 16, 20, this, "windowdesign.tga")
                      , links(0, 20, 5, get_h()-25, this, "windowdesign.tga")
                      , rechts(get_w()-5, 20, 5, get_h()-25, this, "windowdesign.tga")
                      , unten(5, get_h()-5, get_w()-10, 5, this, "windowdesign.tga")
                      , untenl(0, get_h()-5, 5, 5, this, "windowdesign.tga")
                      , untenr(get_w()-5, get_h()-5, 5, 5, this, "windowdesign.tga")
                      , mitte(5, 20, get_w()-10, get_h()-25, this, "windowdesign.tga")
{
    dragged = 0;

    //Display-Listen Zeugs:
    if(!(stranslation = glGenLists(3)))
       return; //Error !!
    drawing = stranslation+1;
    etranslation = drawing+1;

    redraw = true;
    retranslate = true;

    //Design
    oben.set_texcoordinaten(5.0/75.0, 0.0, 6.0/75.0, 20.0/26.0);
    obenl.set_texcoordinaten(0.0, 0.0, 5.0/75.0, 20.0/26.0);
    obenr.set_texcoordinaten(70.0/75.0, 0.0, 1.0, 20.0/26.0);
    but4.set_texcoordinaten(6.0/75.0, 0.0, 22.0/75.0, 20.0/26.0);
    but3.set_texcoordinaten(22.0/75.0, 0.0, 38.0/75.0, 20.0/26.0);
    but2.set_texcoordinaten(38.0/75.0, 0.0, 54.0/75.0, 20.0/26.0);
    but1.set_texcoordinaten(54.0/75.0, 0.0, 70.0/75.0, 20.0/26.0);
    links.set_texcoordinaten(0.0, 20.0/26.0, 5.0/75.0, 21.0/26.0);
    rechts.set_texcoordinaten(70.0/75.0, 20.0/26.0, 1.0, 21.0/26.0);
    unten.set_texcoordinaten(5.0/75.0, 21.0/26.0, 6.0/75.0, 1.0);
    untenl.set_texcoordinaten(0.0, 21.0/26.0, 5.0/75.0, 1.0);
    untenr.set_texcoordinaten(70.0/75.0, 21.0/26.0, 1.0, 1.0);
    mitte.set_texcoordinaten(5.0/75.0, 20.0/26.0, 6.0/75.0, 21.0/26.0);
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

