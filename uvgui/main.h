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
//---------------------------------------------------------------------------

namespace uv_main
{
   uv_config konfig;

   uv_mainwindow mainwindow;
   uv_container cont1;
   //Die Fenster
   uv_window window1, window2, aaa, bbb, ccc, ddd, eee, fff;
   //Die Buttons
   uv_button Button1, Button2;
   //Die Bilder
   uv_image img, test, testa;
   //Die Boxen
   uv_box tst, box1;
   uv_fpscounter fps;
   uv_textbox test1, test2;
   uv_checkbox cbox;
};

//---------------------------------------------------------------------------
#endif
