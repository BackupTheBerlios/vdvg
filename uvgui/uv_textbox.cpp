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
// File:       uv_textbox.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_textbox.h"
//---------------------------------------------------------------------------
uv_textbox::uv_textbox()
{
   //Noch nicht initialisiert
   is_init = false;
};
//---------------------------------------------------------------------------
bool uv_textbox::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(5)))
      return false; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;
   scissoran = etranslation+1;
   scissoraus = scissoran+1;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y, init.width, init.height, init.name, false));  //Warum false ?!?

   init.text_attribute.parent = this;
   text = init.text_attribute;
   text.set_pos(5,((get_h()+text.get_height())/2)-2);
   text.set_cursor(true, 0);

   redraw = true;
   retranslate = true;
   last_abs_x = -1; last_abs_y = -1;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_textbox::attribute uv_textbox::make_attribut(uv_group * parent,
                                     int x, int y, int width, int height,
                                     uv_text::attribute text_attribute,
                                     uv_color color, string name)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.text_attribute = text_attribute;
   attr.color = color; attr.name = name;

   return attr;
};
//---------------------------------------------------------------------------
void uv_textbox::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

   if(retranslate)
   {
      glNewList(stranslation, GL_COMPILE);
         glTranslatef(get_x(), get_y(), 0);
      glEndList();

      glNewList(etranslation, GL_COMPILE);
         glTranslatef(-1*get_x(), -1*get_y(), 0);
      glEndList();

      retranslate = false;
   };

   if(redraw)
   {
      glNewList(drawing, GL_COMPILE);
         glBindTexture(GL_TEXTURE_2D, 0);
         glBegin (GL_QUADS);
            glColor3ub(255, 255, 255);
            glVertex2i (0, 0);             // Links Oben
            glVertex2i (get_w(), 0);       // Rechts Oben
            glVertex2i (get_w(), get_h()); // Rechts Unten
            glVertex2i (0, get_h());       // Links Unten
         glEnd ();
      glEndList();

      redraw = false;
   };

   if(last_abs_x != get_absolute_x() || last_abs_y != get_absolute_y())
   {
      glNewList(scissoran, GL_COMPILE);
         // Nutze Scissor Testing für das clipping des Textes:
         GLint viewport[4];
         glGetIntegerv(GL_VIEWPORT, viewport); //Bildschirmgrösse abholen
         int hight = viewport[3]; //Bildschirmhöhe
         // Definiere die  Scissor Region
         glScissor(get_absolute_x()+3, hight-get_absolute_y()-get_h()+1,
         get_w()-8, get_h()-2);//hight-get_h()+2);
         // aktiviere Scissor Testing
         glEnable(GL_SCISSOR_TEST);
      glEndList();

      glNewList(scissoraus, GL_COMPILE);
         // deaktiviere Scissor Testing
         glDisable(GL_SCISSOR_TEST);
      glEndList();

      last_abs_x = get_absolute_x();
      last_abs_y = get_absolute_y();
   }

   clist->push_back(stranslation);
   clist->push_back(drawing);

   clist->push_back(scissoran);

   //Die childs zeichnen:
   draw_childs(clist);

   clist->push_back(scissoraus);

   clist->push_back(etranslation);
};
//---------------------------------------------------------------------------
bool uv_textbox::key_action(int key, int sym, int mod, int what)
{
   if(SDL_KEYDOWN == what)
   {
      if(key == SDLK_RSHIFT)     return 0;
      if(key == SDLK_LSHIFT)     return 0;
      if(key == SDLK_CAPSLOCK)   return 0;
      if(key == SDLK_NUMLOCK)    return 0;
      if(key == SDLK_SCROLLOCK)  return 0;
      if(key == SDLK_LCTRL)      return 0;
      if(key == SDLK_RCTRL)      return 0;
      if(key == SDLK_RALT)       return 0;
      if(key == SDLK_LALT)       return 0;

      switch(sym)
      {
         case SDLK_DELETE:
            if(pos >= str.length())
               break;
            str.erase(pos, 1);
            break;
         case SDLK_LEFT:
            if(pos==0)
               break;
            --pos;
            break;
         case SDLK_RIGHT:
            if(pos >= str.length())
               break;
            ++pos;
            break;
         case SDLK_HOME:
            pos=0;
            break;
         case SDLK_END:
            pos=str.length();
            break;
         default:
            switch(key)
            {
               case SDLK_BACKSPACE:
                  if(pos==0)
                     break;
                  str.erase(--pos, 1);
                  break;
               default:
                  if(key == 0)
                     break;
                  str.insert(pos++, 1, key);
                  break;
            }; //switch(key)
      };//switch(sym)
   }
   text.pushtext(str);
   text.set_cursor(true, pos);
};
//---------------------------------------------------------------------------
bool uv_textbox::mouse_action(int x, int y,int button,int what)
{
   if(what==SDL_MOUSEBUTTONDOWN && get_visible())
   {
      get_parent()->set_focus(this);
   }
   uv_widget::mouse_action(x,y,button,what);
   return true;
}
//---------------------------------------------------------------------------
