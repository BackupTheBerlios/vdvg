//---------------------------------------------------------------------------
// File:       uv_textbox.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
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
   private:
      uv_group* parent;
      uv_text text;
      char str2[256];
      std::string str;
      int pos;

      int last_abs_x, last_abs_y; //N�tig, um zu pr�fen ob Box verschoben wurde.

      GLuint stranslation, etranslation, drawing, scissoran, scissoraus;
      bool redraw, retranslate;
   public:
      uv_textbox(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel=0);
      void draw(basic_string<GLuint> * clist);
      //bool mouse_action(int x, int y, int button, int what);
      void key_action(int key, int sym, int mod, int what);
      bool mouse_action(int x, int y, int button, int what);
};
//---------------------------------------------------------------------------
#endif
 

