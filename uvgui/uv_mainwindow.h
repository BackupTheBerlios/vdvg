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
// File:       uv_mainwindow.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_MAINWINDOW_
#define _UV_MAINWINDOW_
//---------------------------------------------------------------------------
#include "uv_include.h"

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_mainwindow
 *  @brief Erstellt das Main Window (SDL + OGL)
 *  @author Lukas H
 *  @version 1.0
 *
 *  Verwaltet alle anderen Widgets
 */
//---------------------------------------------------------------------------
class uv_mainwindow:public uv_group
{
public:
   struct attribute
   {
      int width, height;
      bool fullscreen;
      char *caption;
   };
private:
   //Schon initialisiert?
   bool is_init;
   uv_widget *on_top_widget;

   void init_SDL(int breite = 1024, int hoehe = 768, bool fullscreen=true,
                 int bit = 32, int depth_size = 24, int stencil_size = 24,
                 int doublebuffer = 1, int noframe = 0, char *label = 0);
   //Sachen zur Applikationsverwaltung:
   bool is_run;
public:
//   uv_mainwindow(int width, int height, bool fullscreen=1, char * titel=0);
   uv_mainwindow();

   bool initialize(attribute init);
	void set_on_top_widget(uv_widget *);
   bool operator=(attribute init) {return initialize(init);};
   void draw(vector<GLuint> * clist);
   bool key_action(int key, int sym, int mod, int what);
   bool mouse_action(int x, int y, int key, int what);
   void mouse_move_rel(int rel_x, int rel_y);
   void run();
   //Funktionen zur Applikationsverwaltung:
   void set_run(bool Run);
   bool get_run();
   static attribute make_attribut(int widht, int height, bool fullscreen, char *caption);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

