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
/*#include "uv_gui.h"
#include "uv_mainwindow.h"
#include "uv_button.h"
#include "uv_window.h"
#include "uv_image.h"
#include "uv_fpscounter.h"
#include "uv_box.h"
#include "uv_text.h"*/
//---------------------------------------------------------------------------
namespace uv_main
{
   const int width = 1024, height = 768;
   uv_mainwindow mainwindow(width, height, false, "4D4G");

   uv_image img;//(0,0,width,height,&mainwindow,"background.jpg");
   uv_window window1;
   uv_window aaa;
   uv_window bbb;
   uv_window ccc;
   uv_window ddd;
   uv_window eee;
   uv_window fff;
   uv_box tst(20, 110, 200, 100, &window1);
   uv_image test;//(20, 110, 200, 100, &window1,"Testbild2.bmp");
   uv_fpscounter fps(&mainwindow);
   uv_window window2;
   uv_image testa;//(20, 110, 64, 64, &window2,"test3.tga");
   uv_button Button1(30,30,256,64,&window1,"Klick Mich !");
   uv_button Button2(30,30,256,64,&window2,"Beenden");
   uv_textbox test1(10, 30, 266, 20, &aaa, "");
   uv_textbox test2(10, 60, 266, 20, &aaa, "");
   uv_box box1(20, 150, 40, 80, &aaa);
};
//---------------------------------------------------------------------------
#endif
