//---------------------------------------------------------------------------
// File:       uv_textbox.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef uv_textboxH
#define uv_textboxH
//---------------------------------------------------------------------------
#include "uv_group.h"
#include "uv_text.h"
//---------------------------------------------------------------------------
class uv_textbox: public uv_group
{
   public:
      struct attribute
      {
         uv_group * parent;
         int x, y, width, height;
         uv_text::attribute text_attribute;
         uv_color color;
         string name;
      };
      struct callback: public uv_callback
      {

      };
   private:
      uv_text text;
      char str2[256];
      std::string str;
      int pos;

      int last_abs_x, last_abs_y; //Nötig, um zu prüfen ob Box verschoben wurde.

      GLuint stranslation, etranslation, drawing, scissoran, scissoraus;
      bool redraw, retranslate;
   public:
      uv_textbox();

      bool initialize(attribute init);
      bool operator=(attribute init) {return initialize(init);};

      void draw(basic_string<GLuint> * clist);
      void key_action(int key, int sym, int mod, int what);
      bool mouse_action(int x, int y, int button, int what);
      static attribute make_attribut(uv_group * parent,
                                     int x, int y, int width, int height,
                                     uv_text::attribute text_attribute,
                                     uv_color color, string name);
};
//---------------------------------------------------------------------------
#endif
 

