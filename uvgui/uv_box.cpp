//---------------------------------------------------------------------------
// File:       uv_box.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_box.h"
//---------------------------------------------------------------------------
uv_box::uv_box(int mx, int my, int mw, int mh, uv_group *parent):uv_widget(mx, my, mw,mh,parent,0)
{
   //parent->add_child(this);
   uv_box();

   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(3)))
      return; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   redraw = true;
   retranslate = true;
}
//---------------------------------------------------------------------------
uv_box::uv_box():uv_widget(0,0,0,0,0,0)
{
   red=0xff; green=0xff; blue=0xff;
}
//---------------------------------------------------------------------------
void uv_box::draw(basic_string<GLuint> * clist)
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
