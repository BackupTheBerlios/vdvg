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
// File:       uv_fpscounter.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_FPSCOUNTER_H_
#define _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
#include "uv_include.h"
#include "SDL.h"

#include <string>
#include <iostream>
#include <sstream>  //für stringstream
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class uv_fpscounter:public uv_group
{
   public:
      struct attribute
      {
         uv_group * parent;
         int x, y, width, height;
         uv_text::attribute text_attribute;
         string name;
      };
      struct callback: public uv_callback
      {

      };
   private:
      //Schon initialisiert?
      bool is_init;
      uv_text counter;
      std::string IntToString(const int & value);

   public:
      uv_fpscounter();

      bool initialize(attribute init);
      bool operator=(attribute init) {return initialize(init);};

      void draw(vector<GLuint> * clist);

      static attribute make_attribut(uv_group * parent,
                                     int x, int y, int width, int height,
                                     uv_text::attribute text_attribute,
                                     string name);
};
//---------------------------------------------------------------------------
#endif // _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
