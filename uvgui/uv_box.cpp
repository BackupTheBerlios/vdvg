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
*///---------------------------------------------------------------------------
// File:       uv_box.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_box.h"
//---------------------------------------------------------------------------
uv_box::uv_box()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------
bool uv_box::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(3)))
      return false; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   red=0xff; green=0xff; blue=0xff;

   uv_widget::initialize(uv_widget::make_attribut(init.parent, init.x, init.y,
                         init.width, init.height, init.name, false));

   red = init.color.red; green = init.color.green; blue = init.color.blue;

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_box::attribute uv_box::make_attribut(uv_group * parent,
                                        int x, int y, int width, int height,
                                        uv_color color, string name)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.color = color; attr.name = name;

   return attr;
};
//---------------------------------------------------------------------------
void uv_box::draw(vector<GLuint> * clist)
{
   if(retranslate)
   {
      glNewList(stranslation, GL_COMPILE);
      glTranslatef(get_x(), get_y(), 0);
      glEndList();

      glNewList(etranslation, GL_COMPILE);
      glTranslatef(-1*get_x(), -1*get_y(), 0);
      glEndList();

      retranslate = false;
   }

   if(redraw)
   {
      glNewList(drawing, GL_COMPILE);
      glColor3ub(red, green, blue);
      glBegin (GL_QUADS);
         glVertex2i (0,       0);
         glVertex2i (get_w(), 0);
         glVertex2i (get_w(), get_h());
         glVertex2i (0,       get_h());
      glEnd();
      glColor3ub (0,0,0);
      glEndList();

      redraw = false;
   }

   clist->push_back(stranslation);
   clist->push_back(drawing);
   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
