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
// File:       uv_dropdown.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_DROPDOWN_
#define _UV_DROPDOWN_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include "uv_list.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_dropdown
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_dropdown: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
	  uv_mainwindow * mainwindow;	
      int x, y, width, height;
      string name, design;
		vector<string> elements;
   };
   struct callback: public uv_callback
   {
     int num; 
   };
private:
   //Schon initialisiert?
   bool is_init;
   uv_image backa, backb;
   uv_image obenrechts, oben, obenlinks, links, untenlinks, unten, untenrechts, rechts;
   uv_text text; 
   uv_list droplist;
	vector<string> elements;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate; 
   std::string design;
	uv_mainwindow *mainwindow;
	int act_ele;
public:
   uv_dropdown();
	int get_act_ele() { return act_ele;};  
	void set_act_ele(int a); 

   void internalcallback(uv_callback * cb);
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   bool key_action(int key, int sym, int mod, int what);

   static attribute make_attribut(uv_group * parent, uv_mainwindow * mainw,
                                  int x, int y, int width, int height,
                                  string name, vector<string> elemes, string design);
};

static void sta_internalcallback(uv_callback * cb);
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
