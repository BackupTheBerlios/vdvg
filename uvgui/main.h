//---------------------------------------------------------------------------
// File:       main.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
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
uv_mainwindow mainwindow(1024, 768, false, "4D4G");

uv_image img(0,0,1024,768,&mainwindow,"background.jpg");
uv_window window1(50,50,600,300,&mainwindow,"auh");
uv_window aaa(20,20,300,500,&mainwindow,"gjh");
uv_image test(20, 110, 100, 64, &window1,"test3.tga");
uv_fpscounter fps(&mainwindow);
uv_window window2(400,450,300,200,&mainwindow,"jkh");
uv_image testa(20, 110, 64, 64, &window2,"test3.tga");
uv_button Button1(30,30,256,64,&window1,"Klick Mich !");
uv_button Button2(30,30,256,64,&window2,"Beenden");
uv_textbox test1(10, 30, 266, 20, &aaa, "");
};
//---------------------------------------------------------------------------
#endif
