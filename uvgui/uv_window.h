//---------------------------------------------------------------------------
// File:       uv_window.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_WINDOW_H_
#define _UV_WINDOW_H_
//---------------------------------------------------------------------------
#include "uv_group.h"
#include "uv_image.h"
//#include "uv_include.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
//! @class uv_window
//  @brief Erstellt ein Window, welches weitere Widgets enthalten kann.
//  @author Lukas H
//  @version 1.0
//
//  Ein einfaches Fenster
//
//---------------------------------------------------------------------------
class uv_window:public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      string name, caption, icon, design; //Wenn design == "" -> Standarddesign
      bool closebutton, otherbutton, draggable, sizeable;
   };
   struct callback: public uv_callback
   {

   };
private:
   //Fenstereigenschaften:
   string caption, icon, design;
   bool closeexist, otherexist, draggable, sizeable;
   //Wurde das Fenster initialisier?
   bool is_init;

   //Status der Windowbuttons
   bool dragged, close, other;

   //Bilder für das Fensterdesign
   uv_image oben, obenl, obenr, but1, but2, but3, but4, links, rechts,
            unten, untenl, untenr, mitte;

   //CallLists für das Zeichnen des Fensters
   GLuint stranslation, etranslation, drawing;
   bool redraw, retranslate;
public:
//   uv_window(int mx, int mw, int width, int height,uv_group *parent, char * titel=0);
   uv_window();
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};
   bool is_initialized();
   void draw(basic_string<GLuint> * clist);
   void key_action(int key, int sym, int mod, int what);
   bool mouse_action(int x, int y, int key, int what);
   void mouse_move_rel(int rel_x, int rel_y);
   attribute make_attribut(uv_group * partent,
                           int x, int y, int width, int height,
                           string name, string caption,
                           string icon, string design,
                           bool closebutton, bool otherbutton,
                           bool draggable, bool sizeable);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

