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
// File:       uv_widget.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_group.h"
//---------------------------------------------------------------------------
uv_widget::uv_widget()
{
   is_init = false;
};
//---------------------------------------------------------------------------
bool uv_widget::initialize(attribute init)
{
   //Die Geometriedaten setzen:
   x = init.x; y = init.y;
   w = init.width; h = init.height;

   myparent = init.parent;
   label = const_cast<char *>(init.label.c_str());
   visible = true;
   callback = NULL;
   can_focus_have = init.CanFocusHave;

   //Das Child beim Parent eintragen (falls parent != 0):
   if(init.parent!=0)
      myparent->add_child(this);

   mouseover = false;
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_widget::attribute uv_widget::make_attribut(uv_group * parent, int x, int y,
                                              int width, int height,
                                              string label, bool CanFocusHave)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.label = label;
   attr.CanFocusHave = CanFocusHave;

   return attr;
};
//---------------------------------------------------------------------------
uv_widget::~uv_widget()
{

};
//---------------------------------------------------------------------------
int uv_widget::get_absolute_x()
{
    if(myparent)
        return (myparent->get_absolute_x()+get_x());
    return 0;
};
//---------------------------------------------------------------------------
int uv_widget::get_absolute_y()
{
    if(myparent)
        return (myparent->get_absolute_y()+get_y());
    return 0;
};
//---------------------------------------------------------------------------
void uv_widget::set_parent(uv_group *parent)
{
   //Hier muss sich, wenn myparent != 0, das child noch abmelden
   myparent=parent;
   myparent->add_child(this);
}
//---------------------------------------------------------------------------
uv_group* uv_widget::get_parent()
{
   return myparent;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die Breite des Widgets zurück.
int uv_widget::get_w()
{
   return w;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die Höhe des Widgets zurück.
int uv_widget::get_h()
{
   return h;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die relative x-Kooridnate des Widgets zurück.
int uv_widget::get_x()
{
   return x;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die relative y-Koordinate des Widgets zurück.
int uv_widget::get_y()
{
   return y;
};
//---------------------------------------------------------------------------
void uv_widget::set_pos(int x, int y)
{
   this->x = x;
   this->y = y;
};
//---------------------------------------------------------------------------
//Mit dieser Funktion kann man die Grösse und die Position des Widgets ver-
//ändern. Die Werte werden !!nicht!! auf Gültigkeit überprüft.
bool uv_widget::set_size(int x, int y, int width, int height)
{
   this->x=x;
   this->y=y;
   this->w=width;
   this->h=height;

   //Alles OK
   return true;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt das Label des Widgets zurück
char* uv_widget::get_label()
{
   return label;
};
//---------------------------------------------------------------------------
//Wenn visible == false ==> Widget wird nicht gezeichnet
void uv_widget::set_visible(bool visible, bool in_front)
{
   this->visible=visible;
   if(visible && in_front)
      get_parent()->set_focus(this);
};
//---------------------------------------------------------------------------
//Gibt an, ob das Widget sichtbar ist oder nicht.
bool uv_widget::get_visible()
{
   return visible;
};
//---------------------------------------------------------------------------
//Gibt an, ob das Widget den Fokus bekommen kann.
bool uv_widget::kann_focus_haben()
{
   return can_focus_have;
};
//---------------------------------------------------------------------------
//Gibt an, ob sich der Cursor über dem Widget befindet.
bool uv_widget::mouse_over()
{
   return mouseover;
};
//---------------------------------------------------------------------------
//Setz einen Funktionszeiger für Callback
void uv_widget::set_callback(voidcallback callback)
{
   this->callback=callback;
};
//---------------------------------------------------------------------------
//Gibt die Callback Adresse zurück
voidcallback uv_widget::get_callback()
{
   return callback;
};
//---------------------------------------------------------------------------
//Löse den Callback aus
void uv_widget::do_callback(uv_callback * cb)
{
   cb->userpointer = userptr; //zeiger für userdaten
   if(callback)(*callback)(cb);
};
//---------------------------------------------------------------------------
//Setze den Wert, wann der Callback ausgelöst werden soll
void uv_widget::set_when(int bitset)
{
   whenbits = bitset; //Bitmasken werden ueber Defines gesetzt.
};
//---------------------------------------------------------------------------
bool uv_widget::key_action(int key, int sym, int mod, int what)
{

};
//---------------------------------------------------------------------------
bool uv_widget::mouse_action(int x, int y,int button,int what)
{
   if(what==SDL_MOUSEMOTION)
      mouseover = true;
   return true;
};
//---------------------------------------------------------------------------
void uv_widget::mouse_move_rel(int rel_x, int rel_y)
{

};
//---------------------------------------------------------------------------
void uv_widget::set_mouse_over_off()
{
   mouseover = false;
};

void uv_widget::set_userpointer(void *ptr)
{
userptr = ptr;
};//---------------------------------------------------------------------------
