//---------------------------------------------------------------------------
// File:       uv_textbox.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sun Sep-12-2004 21:20:06 by Benny>
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
      uv_text text;
      char str2[256];
      std::string str;
      int pos;
   public:
      uv_textbox(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel=0);
      void draw();
      //bool mouse_action(int x, int y, int button, int what);
      void key_action(int key, int sym, int mod, int what);
};
//---------------------------------------------------------------------------
#endif
 