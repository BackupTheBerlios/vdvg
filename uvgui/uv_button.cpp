//---------------------------------------------------------------------------
// File:       uv_button.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_button.h"
//---------------------------------------------------------------------------
uv_button::uv_button()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------
bool uv_button::initialize(attribute init)
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


   //init.image_attribute.parent = this;
   //image = init.image_attribute;

   uv_color text_color = {0xff, 0x88, 0x00};
   text = uv_text::make_attribut(this, 0, 0, 0, 0, 25, "Buttontext", init.caption, "Test.ttf", text_color);
   text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_button::attribute uv_button::make_attribut(uv_group * parent,
                                              int x, int y, int width, int height,
                                              //uv_image::attribute image_attribute,
                                              string name, string caption, string design)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   //attr.image_attribute = image_attribute;
   attr.name = name; attr.caption = caption;

   return attr;
};
//---------------------------------------------------------------------------
void uv_button::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

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

//   clist->push_back(stranslation);
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

   clist->push_back(stranslation);
   draw_childs(clist);
   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
bool uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONUP && get_visible())//SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 11;
        do_callback(&var);
    }
    uv_widget::mouse_action(x,y,button,what);
    return true;
}
//---------------------------------------------------------------------------
bool uv_button::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 11;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
