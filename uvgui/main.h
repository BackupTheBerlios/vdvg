//---------------------------------------------------------------------------
// File:       main.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
//---------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <sstream>  //für stringstream

#include "uv_include.h"
#include "uv_textbox.h"
#include "uv_config.h"
#include "uv_kithread.h"
#include "uv_dropdown.h"
//---------------------------------------------------------------------------

namespace uv_main
{
   //Allgemein:
   uv_mainwindow mainwindow;
   uv_config konfig;
   uv_fpscounter fps;
	
   //Menue:
   uv_image img1;
   uv_container menu;
   uv_button mnewgame,moptions, mabout, mexit;
   
   //Optionen:
   uv_window options;
   uv_button ook,ocancel;
   uv_checkbox ofullscreen;
   uv_dropdown oresolution;
	vector<string> vec_resolutions;
	uv_text orestext, oinfotext, oinfotextb;
	int oresnumtemp;

   //About:
   uv_window about;

   //Game:
   uv_image img2;
   uv_container	  game;
   uv_gamebutton  gbuttons[256];
   uv_button	  gexit, new_game, exit, ok1, ok2;
   uv_window      lost, won;
   uv_text        verloren, gewonnen1, gewonnen2;

   //Gameoptionen:
   uv_window      gameoptionen;
   uv_button      gook, goleichter, goschwerer;
   uv_text        goschwierigkeitsgrad, goschwierigkeitsstufe, goschwierigkeit;
   uv_text        gospielmodus;
   uv_checkbox    gomenschcomp, gocompmensch, gomenschmensch, gocompcomp;
   bool           compcomp;
   int            spielmodus;

   //Hilfsfunktion
   std::string IntToString(const int & value);
};

//---------------------------------------------------------------------------
#endif
