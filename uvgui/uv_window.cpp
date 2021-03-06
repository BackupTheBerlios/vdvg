/*
-----------------------------------------------------------------------------
4D 4Gewinnt is simple board game.
Copyright (C) 2004 Benny Loeffel, Lukas Humbel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
-----------------------------------------------------------------------------
*/
//---------------------------------------------------------------------------
// File:       uv_window.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_window.h"
//---------------------------------------------------------------------------
uv_window::uv_window()
{
   //Noch nicht initialisiert
   is_init = false;
};
//---------------------------------------------------------------------------
bool uv_window::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(3)))
      return false; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y,
                        init.width, init.height, init.name, true));

   //Wichtige Fenstervariablen setzen
   closeexist = init.closebutton;
   otherexist = init.otherbutton;
   draggable  = init.draggable;
   sizeable   = init.sizeable;

   //Pfade setzen
   //setze label(name)
   caption = init.caption;
   icon    = init.icon;
   design  = (init.design == "") ? static_cast<string>("windowdesign.tga") : init.design;

   oben   = oben.make_attribut(this, 5, 0, get_w()-10, 20, "oben", design, 5.0/75.0, 0.0, 6.0/75.0, 20.0/26.0);
   obenl  = oben.make_attribut(this, 0, 0, 5, 20, "oben", design, 0.0, 0.0, 5.0/75.0, 20.0/26.0);
   obenr  = oben.make_attribut(this, get_w()-5, 0, 5, 20, "oben", design, 70.0/75.0, 0.0, 1.0, 20.0/26.0);
   but1   = oben.make_attribut(this, get_w()-21, 0, 16, 20, "oben", design, 54.0/75.0, 0.0, 70.0/75.0, 20.0/26.0);
   but2   = oben.make_attribut(this, get_w()-21, 0, 16, 20, "oben", design, 38.0/75.0, 0.0, 54.0/75.0, 20.0/26.0);
   but3   = oben.make_attribut(this, get_w()-37, 0, 16, 20, "oben", design, 22.0/75.0, 0.0, 38.0/75.0, 20.0/26.0);
   but4   = oben.make_attribut(this, get_w()-37, 0, 16, 20, "oben", design, 6.0/75.0, 0.0, 22.0/75.0, 20.0/26.0);
   links  = oben.make_attribut(this, 0, 20, 5, get_h()-25, "oben", design, 0.0, 20.0/26.0, 5.0/75.0, 21.0/26.0);
   rechts = oben.make_attribut(this, get_w()-5, 20, 5, get_h()-25, "oben", design, 70.0/75.0, 20.0/26.0, 1.0, 21.0/26.0);
   unten  = oben.make_attribut(this, 5, get_h()-5, get_w()-10, 5, "oben", design, 5.0/75.0, 21.0/26.0, 6.0/75.0, 1.0);
   untenl = oben.make_attribut(this, 0, get_h()-5, 5, 5, "oben", design, 0.0, 21.0/26.0, 5.0/75.0, 1.0);
   untenr = oben.make_attribut(this, get_w()-5, get_h()-5, 5, 5, "oben", design, 70.0/75.0, 21.0/26.0, 1.0, 1.0);
   mitte  = oben.make_attribut(this, 5, 20, get_w()-10, get_h()-25, "oben", design, 5.0/75.0, 20.0/26.0, 6.0/75.0, 21.0/26.0);
   set_in_front(&mitte);

   dragged = false;
   close = false;
   other = false;


   but2.set_visible(false);
   but4.set_visible(false);

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
bool uv_window::is_initialized()
{
   return is_init;
};
//---------------------------------------------------------------------------
void uv_window::draw(vector<GLuint> * clist)
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
    if(what==SDL_MOUSEBUTTONDOWN)
    {
       if(draggable && y < 20 && x >= 5 && x < get_w()-37 && y>0)
          dragged = true; //Mausklick im Drag Bereich

       if(closeexist && y < 20 && x >= get_w()-21 && x < get_w()-5)
       {
          close = true;
          but1.set_visible(false);
          but2.set_visible(true);
       }
       if(otherexist && y < 20 && x >= get_w()-37 && x < get_w()-21)
       {
          other = true;
          but3.set_visible(false);
          but4.set_visible(true);
       }
    }
    if(what==SDL_MOUSEBUTTONUP)
    {
       dragged = false;
       if(closeexist)
       {
          close = false;
          but1.set_visible(true);
          but2.set_visible(false);
       }
       if(otherexist)
       {
          other = false;
          but3.set_visible(true);
          but4.set_visible(false);
       }
    }

    return mouse_action_childs(x, y, button, what);
};
//---------------------------------------------------------------------------
bool uv_window::key_action(int key, int sym, int mod, int what)
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
uv_window::attribute uv_window::make_attribut(uv_group * parent,
                                              int x, int y, int width, int height,
                                              string name, string caption,
                                              string icon, string design,
                                              bool closebutton, bool otherbutton,
                                              bool draggable, bool sizeable)
{
   attribute attri;

   attri.parent = parent;
   attri.x = x; attri.y = y; attri.width = width; attri.height = height;
   attri.name = name; attri.caption = caption;
   attri.icon = icon; attri.design = design;
   attri.closebutton = closebutton; attri.otherbutton = otherbutton;
   attri.draggable = draggable; attri.sizeable = sizeable;

   return attri;
};
//---------------------------------------------------------------------------

