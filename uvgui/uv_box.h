//---------------------------------------------------------------------------
// File:       uv_box.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_BOX_
#define _UV_BOX_
//---------------------------------------------------------------------------
#include "SDL.h"
#include "SDL_opengl.h"
//#include "uv_include.h"
#include "uv_widget.h"
#include "uv_group.h"
//---------------------------------------------------------------------------
class uv_box:public uv_widget
{
   private:
      GLubyte red, green, blue;

      GLuint stranslation, etranslation, drawing;
      bool redraw, retranslate;
   public:
      void draw(basic_string<GLuint> * clist);
      uv_box(int x, int y, int w, int h, uv_group *parent);
      uv_box();
      void set_color(GLubyte red,GLubyte green, GLubyte blue)
      {
	 this->red=red;
	 this->green=green;
	 this->blue=blue;
         redraw = true;
      }
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
