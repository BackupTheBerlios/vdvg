//---------------------------------------------------------------------------
// File:       uv_gamebutton.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_GAMEBUTTON_
#define _UV_GAMEBUTTON_
//---------------------------------------------------------------------------
#include "uv_include.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_gamebutton
 *  @brief Button fuer das Spielfeld
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_gamebutton: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      string name;
   };
   struct callback: public uv_callback
   {
		int status;
   };
private:
   //Schon initialisiert?
   bool is_init;
   int status;
   //std::string textspeicher;
   GLuint stranslation, etranslation, drroh, drx, dro;
   bool redraw, retranslate;
public:
   uv_gamebutton();

   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   void key_action(int key, int sym, int mod, int what);
   static attribute make_attribut(uv_group * parent,
                                  int x, int y, int width, int height, string name);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
