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
// File:       uv_widget.h
// Created by: Lukas Hubmel <luki@humbels.com>
// Created on: Tue Apr 13 00:07:11 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_WIDGET_H_
#define _UV_WIDGET_H_
//---------------------------------------------------------------------------
class uv_group;  //forward-Deklaration von uv_group
//---------------------------------------------------------------------------
#include "uv_gui.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
struct uv_callback
{
   int ID;
   void *userpointer;
};
//---------------------------------------------------------------------------
struct uv_color
{
   GLubyte red, green, blue;
   static uv_color make_color(GLubyte red, GLubyte green, GLubyte blue)
   {
      uv_color color;

      color.red   = red;
      color.green = green;
      color.blue  = blue;

      return color;
   };
};
//---------------------------------------------------------------------------
typedef void (*voidcallback)(uv_callback * cb);
//-------------------------------------------------------------------------//
//  @class uv_widget                                                       //
//  @brief Verwaltet gemeinsame Optionen eines Widgets                     //
//  @author Lukas H                                                        //
//  @version 1.0                                                           //
//                                                                         //
//  Basisklasse f�r alle Widgets, enth�lt Virtuelle Funktionen             //
//                                                                         //
//-------------------------------------------------------------------------//
class uv_widget
{
   public:
      struct attribute
      {
         uv_group * parent;
         int x, y, width, height;
         string label;
         bool CanFocusHave;
      };
   private:
      int x, y, w, h;
      voidcallback callback;
      int whenbits;
      char *label;
      bool visible;
      uv_group *myparent;
      bool can_focus_have;  //Kann das Widget den Focus bekommen?
      bool mouseover;

      //Wurde das Widget initialisier?
      bool is_init;
 	  void *userptr;
   public:
      uv_widget();

      bool initialize(attribute init);
      bool operator=(attribute init) {return initialize(init);};

      static attribute make_attribut(uv_group * parent, int x, int y,
                                     int width, int height, string label="",
                                     bool CanFocusHave=false);

      //Destruktor
      virtual ~uv_widget(); //Macht nichts

      uv_group* get_parent(); //Liefert einen Zeiger auf den Parent zur�ck
      void set_parent(uv_group *parent); //Setze den Zeiger auf den Parent

      int get_w(); //Liefert die breite (width)
      int get_h(); //Liefert die Hoehe (height)
      int get_x(); //Liefert die relative x-Koordinate
      int get_y(); //Liefert die relative y-Koordinate

      int get_absolute_x(); //Liefert die absolute x-Koordinate
      int get_absolute_y(); //Liefert die absolute y-Koordinate

      //Die Position eines Widgets setzen
      void set_pos(int x, int y);
      //Gr�sse und Position eines Widgets ver�ndern/setzen
      bool set_size(int x, int y, int width, int height);

      virtual void draw(vector<GLuint> * clist)=0; //Zeichnet das Widget

      //Setz einen Funktionszeiger f�r Callback
      void set_callback(voidcallback callback);
      //Callback Adresse zur�ckgeben
      voidcallback get_callback();
      void do_callback(uv_callback * cb);
      void set_when(int bitset); //Wann wird der Callback ausgel�st?

      char* get_label();      //Label zurueckgeben

      void set_visible(bool visible, bool in_front=false);  //wenn visible=0, nicht zeichnen
      bool get_visible(); //visible?

      bool kann_focus_haben();
      bool mouse_over();

	  void set_userpointer(void *ptr); //Setzen fuer userbedingte Callback zeiger

      //key=Taste, mod=Modifiers, what=UP,Down
      virtual bool key_action(int key, int sym, int mod, int what);
      virtual bool mouse_action(int x, int y,int button,int what);
      virtual void mouse_move_rel(int rel_x, int rel_y);
      virtual void set_mouse_over_off();
};
//---------------------------------------------------------------------------
#endif	//_UVWIDGET_H_
//---------------------------------------------------------------------------
