/*
-----------------------------------------------------------------------------
4D 4Gewinnt is simple board game.
Copyright (C) 2004 Benny Loeffel, Lukas Humbel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
-----------------------------------------------------------------------------
*/
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
   uv_text aba, abb, abc,abd;
   uv_button aclose;

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
