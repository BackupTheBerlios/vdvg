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
// File:       uv_list.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_LIST_
#define _UV_LIST_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
//#include "uv_include.h"
#include "uv_mainwindow.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <list>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
/*! @class uv_list
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_list: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width;
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
	
	int fontheight;
	int fontspace;
	int mouse_over_ele;
	
	uv_image *elements_backa;
	uv_image *elements_backb;
	uv_image *elements_space;
	uv_text  *elements_text;
   uv_image obenrechts, oben, obenlinks, links, untenlinks, unten, untenrechts, rechts;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate; 
   std::string design;
public:
   uv_list();

	vector<string> elements;
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   bool key_action(int key, int sym, int mod, int what);

   static attribute make_attribut(uv_group * parent,
                                  int x, int y,  int width,
                                  //uv_image::attribute image_attribute,
                                  vector<string> elements, string name, string design);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
