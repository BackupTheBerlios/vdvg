//---------------------------------------------------------------------------
// File:       uv_gamebutton.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_GAMEBUTTON_
#define _UV_GAMEBUTTON_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_gamebutton
 *  @brief Erstellt ein anklickbaren Button
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
  //    uv_image::attribute image_attribute;
      string name, design;
   };
   struct callback: public uv_callback
   {
      bool used;
   };
private:
   //Schon initialisiert?
   bool is_init;
   uv_image backa, backb;
   uv_image obenrechts, oben, obenlinks, links, untenlinks, unten, untenrechts, rechts;
   uv_image statusx, statuso;
   //uv_text text; 
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate; 
   std::string design;
   int status;
public:
   uv_gamebutton();

   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   void key_action(int key, int sym, int mod, int what);
   static attribute make_attribut(uv_group * parent,
                                  int x, int y, int width, int height,
                                  //uv_image::attribute image_attribute,
                                  string name, string design);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
