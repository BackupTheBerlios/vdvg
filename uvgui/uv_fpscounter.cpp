//---------------------------------------------------------------------------
// File:       uv_fpscounter.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_fpscounter.h"
//---------------------------------------------------------------------------
//Der Konstruktor
uv_fpscounter::uv_fpscounter(uv_group *parent)
                             : uv_group(parent->get_w()-100,0,50,20,parent,""),
                               counter(0, 0, 0, 0, this, "Framecounter")
{
   counter.set_color(0xff,0xff,0xff);
   counter.init("Test.ttf",16);
   counter.pushtext("Wait...");
   counter.set_pos(0, counter.get_height());
}
//---------------------------------------------------------------------------
//Eine Hilfsfunktion, um ints in strings zu konvertieren
std::string uv_fpscounter::IntToString(const int & value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
};
//---------------------------------------------------------------------------
void uv_fpscounter::draw(basic_string<GLuint> * clist)
{
   static int frames=0;
   static long tickdiff=0;
   if((SDL_GetTicks() - tickdiff) > 1000)
   {
      counter.pushtext("");
      counter.pushtext("FPS: " + IntToString(frames));
      tickdiff = SDL_GetTicks();
      frames=0;
   }
   frames++;
   draw_childs(clist);
};
//---------------------------------------------------------------------------
