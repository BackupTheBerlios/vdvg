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
// File:       uv_group.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_GROUP_
#define _UV_GROUP_
//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_array.h"
#include <vector>	//Childs speichern

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
/*! @class uv_group
 *  @brief Verwaltet gemeinsame Optionen fuer alle Widgets mit Childs
 *  @author Lukas H
 *  @version 1.0
 *
 *  Diese Klasse enthÃ¤lt funktionen, die die Verwaltung von Childs unterstuetzen.
 */
//---------------------------------------------------------------------------
class uv_group:public uv_widget
{
   public:
      struct attribute
      {
         uv_group * parent;
         int x, y, width, height;
         string label;
         bool can_focus_have;
      };
      struct callback: public uv_callback
      {

      };
   private:
      dstack<uv_widget *> childs;
      bool next_child;
      bool last_child;

      bool is_init;
   public:
      uv_group();

      bool initialize(attribute init);
      bool operator=(attribute init) {return initialize(init);};

      uv_widget* get_next_child();
      uv_widget* get_last_child();
      void set_start_child(); 		//Iterator == 0
      void set_end_child();
      void mouse_move_rel(int rel_x, int rel_y);
      void add_child(uv_widget*);
      void remove_child(uv_widget* widget);
      void add_child_in_front(uv_widget* );
      void set_to_end();
      bool draw_childs(vector<GLuint> * clist);
      bool mouse_action_childs(int x, int y, int button, int what);
      bool key_action_childs(int key, int sym, int mod, int what);
      bool mouse_move_rel_childs(int rel_x, int rel_y);
      void set_mouse_over_off();
      bool set_focus(uv_widget * widgetpointer);
      bool set_in_front(uv_widget * widgetpointer);

      static attribute make_attribut(uv_group * parent,
                                     int x, int y, int width, int height,
                                     string label, bool can_focus_have);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
