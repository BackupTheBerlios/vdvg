//---------------------------------------------------------------------------
// File:       uv_fpscounter.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_fpscounter.h"
//---------------------------------------------------------------------------
//Der Konstruktor
uv_fpscounter::uv_fpscounter():uv_group(0,0,0,0,0,"")
{
   //macht momentan nichts
}
//---------------------------------------------------------------------------
bool uv_fpscounter::initialize(attribute init)
{
   set_parent(init.parent);
   set_size(init.x, init.y, init.width, init.height);

   init.text_attribute.parent = this;
   counter = init.text_attribute;
   counter.set_pos(0, counter.get_height());
   return true;
};
//---------------------------------------------------------------------------
uv_fpscounter::attribute uv_fpscounter::make_attribut(uv_group * parent,
                                        int x, int y, int width, int height,
                                        uv_text::attribute text_attribute,
                                        string name)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.text_attribute = text_attribute; attr.name = name;

   return attr;
};
//---------------------------------------------------------------------------
//Eine Hilfsfunktion, um ints in strings zu konvertieren
std::string uv_fpscounter::IntToString(const int & value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
};
//---------------------------------------------------------------------------
void uv_fpscounter::draw(vector<GLuint> * clist)
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
