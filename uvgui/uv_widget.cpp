//---------------------------------------------------------------------------
// File:       uv_widget.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_group.h"
//---------------------------------------------------------------------------
uv_widget::uv_widget(int x, int y, int width, int height, uv_group *parent,
                     char *label, bool CanFocusHave)
{
   this->x=x; this->y=y;
   w=width; h=height;

   myparent=parent;
   this->label=label;
   visible=true;
   callback=NULL;
   can_focus_have=CanFocusHave;

   //Das Child beim Parent eintragen (wenn parent != 0)
   if(parent!=0)
      myparent->add_child(this);

   mouseover = false;
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
//Diese Funktion gibt die Breite des Widgets zur�ck.
int uv_widget::get_w()
{
   return w;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die H�he des Widgets zur�ck.
int uv_widget::get_h()
{
   return h;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die relative x-Kooridnate des Widgets zur�ck.
int uv_widget::get_x()
{
   return x;
};
//---------------------------------------------------------------------------
//Diese Funktion gibt die relative y-Koordinate des Widgets zur�ck.
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
//Mit dieser Funktion kann man die Gr�sse und die Position des Widgets ver-
//�ndern. Die Werte werden !!nicht!! auf G�ltigkeit �berpr�ft.
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
//Diese Funktion gibt das Label des Widgets zur�ck
char* uv_widget::get_label()
{
   return label;
};
//---------------------------------------------------------------------------
//Wenn visible == false ==> Widget wird nicht gezeichnet
void uv_widget::set_visible(bool visible)
{
   this->visible=visible;
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
//Gibt an, ob sich der Cursor �ber dem Widget befindet.
bool uv_widget::mouse_over()
{
   return mouseover;
};
//---------------------------------------------------------------------------
//Setz einen Funktionszeiger f�r Callback
void uv_widget::set_callback(voidcallback callback)
{
   this->callback=callback;
};
//---------------------------------------------------------------------------
//Gibt die Callback Adresse zur�ck
voidcallback uv_widget::get_callback()
{
   return callback;
};
//---------------------------------------------------------------------------
//L�se den Callback aus
void uv_widget::do_callback(uv_callback * cb)
{
   if(callback)(*callback)(cb);
};
//---------------------------------------------------------------------------
//Setze den Wert, wann der Callback ausgel�st werden soll
void uv_widget::set_when(int bitset)
{
   whenbits = bitset; //Bitmasken werden ueber Defines gesetzt.
};
//---------------------------------------------------------------------------
void uv_widget::key_action(int key, int sym, int mod, int what)
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
//---------------------------------------------------------------------------
