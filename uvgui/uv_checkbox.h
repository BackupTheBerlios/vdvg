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
#ifndef _UV_CHECKBOX_
#define _UV_CHECKBOX_

#include "uv_include.h"
#include <SDL.h>
#include <SDL_opengl.h>

class uv_checkbox: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      uv_image::attribute image_unchecked, image_checked;
      uv_text::attribute text_attribute;
      string name;//, caption;
   };
   struct callback: public uv_callback
   {
      bool checked;
   };
private:
   bool is_init;
   bool checked;
   uv_text text;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing;
   bool redraw, retranslate;
   uv_image uncheckimage, checkimage;
public:
   uv_checkbox();
   bool get_checked() {return checked;};
   void set_checked(bool c) {checked=c;};
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   bool key_action(int key, int sym, int mod, int what);
   static attribute make_attribut(uv_group * parent, int x, int y,
                                  int width, int height, uv_image::attribute image_unchecked, uv_image::attribute image_checked,
                                  uv_text::attribute text_attribute, string name);
};

#endif	

