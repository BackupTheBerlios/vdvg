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
// File:       uv_text.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_TEXT_
#define _UV_TEXT_
//---------------------------------------------------------------------------
//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <freetype/internal/ftdebug.h>
#include <freetype/internal/ftstream.h>
#include <freetype/internal/sfnt.h>
#include <freetype/ttnameid.h>
//---------------------------------------------------------------------------
//SDL Headers
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
//---------------------------------------------------------------------------
//Eigene Headers
#include "uv_widget.h"
#include "uv_group.h"
//---------------------------------------------------------------------------
//Und noch ein bisschen STL
#include <iostream>
#include <vector>
#include <string>
#include <map>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
struct font_set
{
   const char *filename;
   unsigned int size;
   bool operator<(const font_set &t) const
   {
      if( size < t.size ) return true;
      if( size > t.size ) return false;
      for(int i=0;;i++)
      {
	 if( filename[i] < t.filename[i]) return true;
	 if( filename[i] > t.filename[i]) return false;
	 if( !(filename[i] && t.filename[i]) ) return false; //Die beiden sind gleich
      }
   };
};
//---------------------------------------------------------------------------
// Drawing routines are stolen from Nehe, Lesson 46 (Man erkennt davon fast
// nichts mehr) 
//---------------------------------------------------------------------------
class uv_text:public uv_widget
{
   private:
      struct font_set
      {
         // Variabeln von "FreeType 2":
         FT_Face face;
         FT_Library library;
         string family_name, style_name;
         unsigned int height, ID;
         GLuint * textures; // Array mit den Textur IDs
         GLuint list_base;  // Variable mit der ID der ersten "display list"
         long* bbreiten;    // ACHTUNG: Keine delete[] !!!!!!!!!!
         bool bbreiteninit;
         bool kerning_support; //wird kerning unterst�tzt?
        // font_set();
        // ~font_set();
         bool free();
      };
   public:
      struct attribute
      {
         uv_group * parent;
         int x, y, width, height, font_size;
         string name, text, font;
         uv_color font_color;
      };
      struct callback: public uv_callback
      {

      };
   private:
      //Schon initialisiert?
      bool is_init;

      //Container mit den Font-Sets:
      static dstack<font_set> font_sets;
      int fontindex;

      float len;

      bool draw_cursor; //Soll ein Cursor gezeichnet werden
      int cursor_position; //Wo befindet sich der Cursor?

      string line;
      uv_color font_color; //Textfarbe
      GLubyte red, green, blue; //Textfarbe

      //Funktionen:
      void splitup(); //text -> lines
      void pop_projection_matrix();
      inline int next_p2 (int a) //Gibt die n�chstgr�ssere 2er Potenz an
      {
         int rval=1; while(rval<a) rval<<=1; return rval;
      };
      void make_dlist(FT_Face face, unsigned char ch, GLuint list_base, GLuint * tex_base);
//      void find_unicode_charmap(FT_Face face);

      GLuint stranslation, etranslation, drawing;
      bool redraw, retranslate;
      int last_abs_x, last_abs_y; //N�tig, um zu pr�fen ob verschoben wurde.
      bool init(const char * fname, unsigned int height);
   public:
      //Konstruktor
      uv_text();
      ~uv_text();

      bool initialize(attribute init);
      bool operator=(attribute init) {return initialize(init);};

      static attribute make_attribut(uv_group * parent,
                                     int x, int y, int width, int height,
                                     int font_size,
                                     string name, string text,
                                     string font, uv_color font_color);

      //Funktionen zur Schriftenverwaltung:
      bool load_font(const char * fname, unsigned int height);
      bool load_font(string fname, unsigned int height);
//      bool delete_font(); // Z�hlt herunter und l�scht wenn n�tig den Font
//      bool delete_font_always(); //L�scht den Font sofort

      void set_color(GLubyte red,GLubyte green,GLubyte blue);
      bool set_cursor(bool draw_cursor, int position);
      void clean();
      void pushtext(string str);
      void print(int x, int y);
      int get_height();
      int get_width(int pos=-1);
      void draw(vector<GLuint> * clist);
};
//---------------------------------------------------------------------------
#endif // _UV_TEXT_
//---------------------------------------------------------------------------
