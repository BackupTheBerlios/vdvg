//---------------------------------------------------------------------------
// File:       uv_dropdown.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_DROPDOWN_
#define _UV_DROPDOWN_
//---------------------------------------------------------------------------
//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include "uv_list.h"
#include "uv_image.h"
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
/*! @class uv_dropdown
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
//---------------------------------------------------------------------------
class uv_dropdown: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
	  uv_mainwindow * mainwindow;	
      int x, y, width, height;
      string name, design;
		vector<string> elements;
   };
   struct callback: public uv_callback
   {
     int num; 
   };
private:
   //Schon initialisiert?
   bool is_init;
   uv_image backa, backb;
   uv_image obenrechts, oben, obenlinks, links, untenlinks, unten, untenrechts, rechts;
   uv_text text; 
   uv_list droplist;
	vector<string> elements;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing1, drawing2;
   bool redraw, retranslate; 
   std::string design;
	uv_mainwindow *mainwindow;
public:
   uv_dropdown();

   void internalcallback(uv_callback * cb);
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   bool key_action(int key, int sym, int mod, int what);

   static attribute make_attribut(uv_group * parent, uv_mainwindow * mainw,
                                  int x, int y, int width, int height,
                                  string name, vector<string> elemes, string design);
};

static void sta_internalcallback(uv_callback * cb);
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
