//---------------------------------------------------------------------------
// File:       uv_gamebutton.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_gamebutton.h"
//---------------------------------------------------------------------------
uv_gamebutton::uv_gamebutton()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------
bool uv_gamebutton::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(4)))
      return false; //Error !!
   drawing1 = stranslation+1;
   drawing2 = drawing1+1;
   etranslation = drawing2+1;
   
   redraw = true;
   retranslate = true;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y, init.width, init.height, init.name, true));

  pos = init.pos;

  design  = (init.design == "") ? static_cast<string>("buttondesign.tga") : init.design;

  obenlinks  = oben.make_attribut(this, 0,  0, 5, 5, "oben", design, 0, 0,         1.0/3.0, 1/3.0);
  links      = oben.make_attribut(this, 0, 5, 5, get_h()-10, "oben", design, 0, 1.0/3.0,     1.0/3.0, 2.0/3.0);
  untenlinks = untenlinks.make_attribut(this, 0, get_h()-5, 5, 5, "oben", design, 0, 2.0/3.0,     1.0/3.0, 1);
	
  unten      = oben.make_attribut(this, 5, get_h()-5, get_w()-10, 5, "oben", design, 1.0/3.0, 2.0/3.0, 2.0/3.0, 3.0/3.0);
  untenrechts= oben.make_attribut(this, get_w()-5, get_h()-5, 5, 5, "oben", design, 2.0/3.0, 2/3.0, 3/3.0, 3/3.0);
  rechts     = oben.make_attribut(this, get_w()-5, 5, 5, get_h()-10, "oben", design, 2.0/3.0, 1/3.0, 3/3.0, 2/3.0); 
  obenrechts = oben.make_attribut(this, get_w()-5, 0, 5, 5, "oben", design, 2/3.0, 0,       3/3.0, 1/3.0);
  oben       = oben.make_attribut(this, 5, 0, get_w()-10, 5, "oben", design, 1/3.0, 0, 2/3.0, 1/3.0);

  backa      = oben.make_attribut(this, 5, 5, get_w()-10, get_h()-10, "oben", design, 5/15.0, 5/15.0, 6/15.0, 6/15.0);
  backb      = oben.make_attribut(this, 5, 5, get_w()-10, get_h()-10, "oben", design, 6/15.0, 5/15.0, 7/15.0, 6/15.0);
  
  statusx    = oben.make_attribut(this, 5, 5, get_w()-10, get_h()-10, "oben", "x.tga");
  statuso    = oben.make_attribut(this, 5, 5, get_w()-10, get_h()-10, "oben", "o.tga");
  statusx.set_visible(0);
  statuso.set_visible(0);
  status = 0;


   //init.image_attribute.parent = this;
   //image = init.image_attribute;

   //uv_color text_color = {0xff, 0x88, 0x00};
   //text = uv_text::make_attribut(this, 0, 0, 0, 0, 25, "Buttontext", init.caption, "Test.ttf", text_color);
   //text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_gamebutton::attribute uv_gamebutton::make_attribut(uv_group * parent,
                                              int x, int y, int width, int height,
                                              //uv_image::attribute image_attribute,
                                              position pos, string name, string design)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   //attr.image_attribute = image_attribute;
   attr.pos = pos;
   attr.name = name;
   return attr;
};
//---------------------------------------------------------------------------
bool uv_gamebutton::set_blink(double time)
{
   new_blink = true;
   blink = true;
   this->time = static_cast<int>(time) * 1000;
};
//---------------------------------------------------------------------------
void uv_gamebutton::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

   bool draw_blink = true;

   if(blink)
   {
      if(new_blink)
      {
         tickdiff = SDL_GetTicks();
         new_blink = false;
      }
      unsigned int speicher = (SDL_GetTicks() - tickdiff);
      if(time > speicher)
      {
         if(speicher > 1000)
         {
            time -= speicher;
            tickdiff = SDL_GetTicks();
         }
         if(speicher > 500)
            draw_blink = false;
         else
            draw_blink = true;
      }
      else
      {
         blink = false;
         draw_blink = true;
      }
   };

   if(retranslate)
   {
      glNewList(stranslation, GL_COMPILE);
      glTranslatef(get_x(), get_y(), 0);
      glEndList();

      glNewList(etranslation, GL_COMPILE);
      glTranslatef(-1*get_x(), -1*get_y(), 0);
      glEndList();

      retranslate = false;
   }

   if(redraw)
   {
      redraw = false;
   }

   // clist->push_back(stranslation);
   if(!mouse_over())
   {
     backa.set_visible(1);
     backb.set_visible(0);
   }
   else
   {
     backa.set_visible(0);
     backb.set_visible(1);
   }
   if(status == 0 || !draw_blink) {statusx.set_visible(0); statuso.set_visible(0);};
   if(status == 1 && draw_blink)  {statusx.set_visible(1); statuso.set_visible(0);};
   if(status == 2 && draw_blink)  {statuso.set_visible(1); statusx.set_visible(0);};

   clist->push_back(stranslation);
   draw_childs(clist);
   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
bool uv_gamebutton::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 18;
        var.pos = pos;
        do_callback(&var);
//		if(status < 2) status++;
//	    else status=0;

    }
        uv_widget::mouse_action(x,y,button,what);
    return true;
}
//---------------------------------------------------------------------------
void uv_gamebutton::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 18;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
bool uv_gamebutton::set_status(int status)
{
   if(status > 2 || status < 0)
      return false;
   this->status = status;
   return true;
}
//---------------------------------------------------------------------------
int uv_gamebutton::get_status()
{
   return status;
};
//---------------------------------------------------------------------------
