//---------------------------------------------------------------------------
// File:       uv_button.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_BUTTON_
#define _UV_BUTTON_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_button
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_button: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      string name, caption;
   };
   struct callback: public uv_callback
   {
      bool used;
   };
private:
   uv_text text;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate;
public:
   uv_button();

   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(basic_string<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   void key_action(int key, int sym, int mod, int what);
   static attribute make_attribut(uv_group * parent,
                                  int x, int y, int width, int height,
                                  string name, string caption);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
