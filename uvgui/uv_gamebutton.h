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
// File:       uv_gamebutton.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_GAMEBUTTON_
#define _UV_GAMEBUTTON_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_gamebutton
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_gamebutton: public uv_group
{
public:
   struct position
   {
      int x_pos, y_pos, z_pos, u_pos;
   };
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
  //    uv_image::attribute image_attribute;
      position pos;
      string name, design;
   };
   struct callback: public uv_callback
   {
      bool used;

      position pos;
   };
private:
   //Schon initialisiert?
   bool is_init;
   uv_image backa, backb;
   uv_image obenrechts, oben, obenlinks, links, untenlinks, unten, untenrechts, rechts;
   uv_image statusx, statuso;
   //uv_text text; 
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate;
   std::string design;
   int status;
   position pos;

   //Für das blinken
   unsigned int time; //Die Dauer, die der Button noch blinken soll
   long tickdiff;
   bool blink;  //Gibt an, ob der Gamebutton blinken soll
   bool new_blink; //Gibt an, ob der Timer neu initialisiert werden muss
public:
   uv_gamebutton();

   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   bool set_blink(double time);
   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   bool set_status(int status);
   bool key_action(int key, int sym, int mod, int what);
   int  get_status();
   static attribute make_attribut(uv_group * parent,
                                  int x, int y, int width, int height,
                                  //uv_image::attribute image_attribute,
                                  position pos, string name, string design);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
