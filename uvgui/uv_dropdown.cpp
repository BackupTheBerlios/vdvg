//---------------------------------------------------------------------------
// File:       uv_dropdown.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_dropdown.h"
//---------------------------------------------------------------------------
uv_dropdown::uv_dropdown()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------


bool uv_dropdown::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(4)))
      return false; //Error !!
   drawing1 = stranslation+1;
   drawing2 = drawing1+1;
   etranslation = drawing2+1;
   
   redraw = true;
   retranslate = true;
	act_ele = -1;

	mainwindow = init.mainwindow;

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

	droplist = uv_list::make_attribut(this, 0,get_h(),200, init.elements, "","");	
	droplist.set_visible(0);
	droplist.set_userpointer(this);
	droplist.set_callback(sta_internalcallback);
	
   //init.image_attribute.parent = this;
   //image = init.image_attribute;

   uv_color text_color = {0xff, 0x88, 0x00};
   text = uv_text::make_attribut(this, 0, 0, 0, 0, 16, "Buttontext", init.elements[0], "Test.ttf", text_color);
   text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_dropdown::attribute uv_dropdown::make_attribut(uv_group * parent, uv_mainwindow * mw,
                                              int x, int y, int width, int height,
                                              string name, vector<string> elemes, string design)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   //attr.image_attribute = image_attribute;
   attr.name = name; attr.elements = elemes; attr.mainwindow = mw;

   return attr;
};
//---------------------------------------------------------------------------
void uv_dropdown::draw(vector<GLuint> * clist)
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
bool uv_dropdown::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible() && mouse_over())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 22;
        do_callback(&var);
		droplist.set_visible(!droplist.get_visible());
		if(droplist.get_visible())
		{
			mainwindow->set_on_top_widget(&droplist);
		}
		else
		{
			mainwindow->set_on_top_widget(0);
		}
    }
    uv_widget::mouse_action(x,y,button,what);
    return true;
}
//---------------------------------------------------------------------------
bool uv_dropdown::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 22;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
void uv_dropdown::internalcallback(uv_callback * cb)
{
	if(cb->ID == 21) //zur sicherheit...
	{
		uv_list::callback * tmp;
        tmp = static_cast<uv_list::callback*>(cb);
		act_ele = tmp->num;
		text.pushtext(droplist.elements[act_ele]);
   		text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);
		callback tep;
		tep.ID=22;
		tep.num = tmp->num;
		do_callback(&tep);

	}
}

static void sta_internalcallback(uv_callback * cb)
{
	uv_dropdown *tmp;
	tmp = (uv_dropdown*) (cb->userpointer);
	tmp->internalcallback(cb);
}

void uv_dropdown::set_act_ele(int a)
{
		act_ele = a;
		text.pushtext(droplist.elements[act_ele]);
}

