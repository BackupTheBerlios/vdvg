//---------------------------------------------------------------------------
// File:       main.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
//---------------------------------------------------------------------------
#include "uv_include.h"
#include "uv_textbox.h"
#include "uv_config.h"
#include "uv_kithread.h"
//---------------------------------------------------------------------------

namespace uv_main
{
   //Allgemein:
   uv_mainwindow mainwindow;
   uv_config konfig;
   uv_image img;
   uv_fpscounter fps;
	
   //Menue:
   uv_container menu;
   uv_button mnewgame,moptions, mabout, mexit;
   
   //Optionen:
   uv_window options;

   //About:
   uv_window about;

   //Game:
   uv_container	  game;
   uv_gamebutton  gbuttons[256];
   uv_button	  gexit, new_game, exit, ok1, ok2;
   uv_window      lost, won;
   uv_text        verloren, gewonnen;
};

//---------------------------------------------------------------------------
#endif
