//---------------------------------------------------------------------------
// File:       main.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
void calli(uv_callback * cb);      //Button1 Action
void calli2(uv_callback * cb);     //Button2 Action
void mainloop(uv_callback * cb);   //Hauptschleife
void fensterinit();
//---------------------------------------------------------------------------
//Hauptprogramm
int main (int argc, char *argv[])
{

   uv_main::konfig.load_file("config.txt");
//   uv_main::mainwindow = uv_mainwindow::make_attribut(1024, 768, false, "4D4G");
   uv_main::mainwindow = uv_main::konfig.get_mainwindow_attribute(); 
   uv_main::mainwindow.set_callback(mainloop);
   uv_main::img = uv_image::make_attribut(&uv_main::mainwindow, 0, 0, uv_main::konfig.get_config().width, uv_main::konfig.get_config().height, "Hintergrund", "background.jpg");
   uv_main::test = uv_image::make_attribut(&uv_main::window1, 20, 110, 200, 100, "test", "Testbild2.bmp", 0.5, 0.0, 1.0, 1.0);
   uv_main::testa = uv_image::make_attribut(&uv_main::window2, 20, 110, 64, 64, "testa","test3.tga");
   fensterinit();
   uv_main::Button1 = uv_button::make_attribut(&uv_main::window1, 30, 30, 256, 64, "Button1", "Klick Mich !");
   uv_main::Button2 = uv_button::make_attribut(&uv_main::window2, 30, 30, 256, 64, "Button2", "Beenden");
   uv_main::tst = uv_box::make_attribut(&uv_main::window1, 20, 110, 200, 100, uv_color::make_color(0, 0, 0), "tst box");
   uv_main::box1 = uv_box::make_attribut(&uv_main::aaa, 20, 150, 40, 80, uv_color::make_color(0, 0, 0), "box1");
   uv_main::test1 = uv_textbox::make_attribut(&uv_main::aaa, 10, 30, 266, 20, uv_text::make_attribut(0, 0, 0, 0, 0, 16, "Text", "", "Test.ttf", uv_color::make_color(0, 0, 0)), uv_color::make_color(255, 255, 255), "Textbox1");
   uv_main::test2 = uv_textbox::make_attribut(&uv_main::aaa, 10, 60, 266, 20, uv_text::make_attribut(0, 0, 0, 0, 0, 16, "Text", "", "Franklin-Italic.ttf", uv_color::make_color(255, 128, 0)), uv_color::make_color(255, 255, 255), "Textbox1");
   uv_main::Button1.set_callback((voidcallback) calli);
   uv_main::Button2.set_callback((voidcallback) calli2);
   uv_main::fps = uv_fpscounter::make_attribut(&uv_main::mainwindow, uv_main::mainwindow.get_w()-100, 0, 0, 0, uv_text::make_attribut(0, 0, 0, 0, 0, 16, "Frames", "Wait...", "Test.ttf", uv_color::make_color(255, 255, 255)),"FPS Counter");
   uv_main::mainwindow.run();
   uv_main::konfig.save_file("config.txt");
   return 0;
};
//---------------------------------------------------------------------------
void mainloop(uv_callback * cb)
{
    //momentan noch leer
};
//---------------------------------------------------------------------------
void calli(uv_callback * cb)
{
    uv_main::Button2.set_visible(!uv_main::Button2.get_visible());
};
//---------------------------------------------------------------------------
void calli2(uv_callback * cb)
{
    if(cb->ID != 11)
       return;
    uv_button::callback * butpointer = static_cast<uv_button::callback *>(cb);
    int i = butpointer->ID;
    bool b = butpointer->used;
    uv_main::mainwindow.set_run(false);
};
//---------------------------------------------------------------------------
void fensterinit()
{
   uv_main::window1 = uv_window::make_attribut(&uv_main::mainwindow, 50, 50, 600, 300, "window1", "window1", "", "", true, true, true, false);
   uv_main::window2 = uv_window::make_attribut(&uv_main::mainwindow, 400, 450, 300, 200, "window2", "window2", "", "", true, true, true, false);
   uv_main::aaa = uv_window::make_attribut(&uv_main::mainwindow, 20, 20, 300, 500, "window2", "window2", "", "", true, true, true, false);
   uv_main::bbb = uv_window::make_attribut(&uv_main::mainwindow, 45, 45, 300, 500, "window2", "window2", "", "", true, true, true, false);
   uv_main::ccc = uv_window::make_attribut(&uv_main::mainwindow, 70, 70, 300, 500, "window2", "window2", "", "", true, true, true, false);
   uv_main::ddd = uv_window::make_attribut(&uv_main::mainwindow, 95, 95, 300, 500, "window2", "window2", "", "", true, true, true, false);
   uv_main::eee = uv_window::make_attribut(&uv_main::mainwindow, 120, 120, 300, 500, "window2", "window2", "", "", true, true, true, false);
   uv_main::fff = uv_window::make_attribut(&uv_main::mainwindow, 145, 145, 300, 500, "window2", "window2", "", "", true, true, true, false);
};
//---------------------------------------------------------------------------




