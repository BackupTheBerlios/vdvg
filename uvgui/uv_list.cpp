//---------------------------------------------------------------------------
// File:       uv_list.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_list.h"
//---------------------------------------------------------------------------
uv_list::uv_list()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------
bool uv_list::initialize(attribute init)
{
   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(4)))
      return false; //Error !!
   drawing1 = stranslation+1;
   drawing2 = drawing1+1;
   etranslation = drawing2+1;
	
	fontheight = 16;
	fontspace = 6;
	mouse_over_ele = -1;
	
 	elements = init.elements;
	int height = init.elements.size() * (fontheight + fontspace) + 10 + fontspace;
   
   redraw = true;
   retranslate = true;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y, init.width, height, init.name, true));

  design  = (init.design == "") ? static_cast<string>("buttondesign.tga") : init.design;

  obenlinks  = oben.make_attribut(this, 0,  0, 5, 5, "oben", design, 0, 0,         1.0/3.0, 1/3.0);
  links      = oben.make_attribut(this, 0, 5, 5, get_h()-10, "oben", design, 0, 1.0/3.0,     1.0/3.0, 2.0/3.0);
  untenlinks = untenlinks.make_attribut(this, 0, get_h()-5, 5, 5, "oben", design, 0, 2.0/3.0,     1.0/3.0, 1);
	
  unten      = oben.make_attribut(this, 5, get_h()-5, get_w()-10, 5, "oben", design, 1.0/3.0, 2.0/3.0, 2.0/3.0, 3.0/3.0);
  untenrechts= oben.make_attribut(this, get_w()-5, get_h()-5, 5, 5, "oben", design, 2.0/3.0, 2/3.0, 3/3.0, 3/3.0);
  rechts     = oben.make_attribut(this, get_w()-5, 5, 5, get_h()-10, "oben", design, 2.0/3.0, 1/3.0, 3/3.0, 2/3.0); 
  obenrechts = oben.make_attribut(this, get_w()-5, 0, 5, 5, "oben", design, 2/3.0, 0,       3/3.0, 1/3.0);
  oben       = oben.make_attribut(this, 5, 0, get_w()-10, 5, "oben", design, 1/3.0, 0, 2/3.0, 1/3.0);

	elements_backa = new uv_image[init.elements.size()];
	elements_backb = new uv_image[init.elements.size()];
	elements_space = new uv_image[init.elements.size()+1];
	elements_text  = new uv_text[init.elements.size()];

   uv_color text_color = {0xff, 0x88, 0x00};

	for(int i=0; i<elements.size(); i++)
	{	
		
		elements_space[i] = uv_image::make_attribut(this,5,5+i*(fontheight+fontspace), get_w()-10, fontspace,"lala",design, 5/15.0, 5/15.0, 6/15.0, 6/15.0);
		elements_backa[i] = uv_image::make_attribut(this,5,5+fontspace+i*(fontheight+fontspace), get_w()-10, fontheight,"lala",design, 5/15.0, 5/15.0, 6/15.0, 6/15.0);
		elements_backb[i] = uv_image::make_attribut(this,5, 5+fontspace+i*(fontheight+fontspace), get_w()-10, fontheight,"lala",design, 6/15.0, 5/15.0, 7/15.0, 6/15.0);
		elements_text[i]  = 	uv_text::make_attribut(this,5, 5+fontspace+i*(fontheight+fontspace)+fontheight-1, get_w()-10, fontheight, fontheight, "Buttontext", elements[i], "Test.ttf", text_color);
		elements_text[i].set_pos((get_w()-elements_text[i].get_width())/2, 5+fontspace+i*(fontheight+fontspace)+fontheight-1);
		elements_backb[i].set_visible(0);
	}
	elements_space[elements.size()] = uv_image::make_attribut(this,5,5+elements.size()*(fontheight+fontspace), get_w()-10, fontspace,"lala",design, 5/15.0, 5/15.0, 6/15.0, 6/15.0);



   //init.image_attribute.parent = this;
   //image = init.image_attribute;

   //text = uv_text::make_attribut(this, 0, 0, 0, 0, 25, "Buttontext", init.caption, "Test.ttf", text_color);
   //text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);

   redraw = true;
   retranslate = true;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_list::attribute uv_list::make_attribut(uv_group * parent,
                                              int x, int y, int width,
                                              //uv_image::attribute image_attribute,
                                              vector<string> elements, string name, string design)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; 
   //attr.image_attribute = image_attribute;
   attr.elements = elements; attr.name = name;

   return attr;
};
//---------------------------------------------------------------------------
void uv_list::draw(vector<GLuint> * clist)
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
		for(int i=0; i<elements.size(); i++)
		{
				
				if(mouse_over_ele == i && mouse_over())
				{
					elements_backb[i].set_visible(1);
					elements_backa[i].set_visible(0);
				}
				else
				{
					elements_backb[i].set_visible(0);
					elements_backa[i].set_visible(1);
	
				}
		}
  
   clist->push_back(stranslation);
   draw_childs(clist);
   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
bool uv_list::mouse_action(int x, int y,int button,int what)
{
	//Callback:
    if( what==SDL_MOUSEBUTTONDOWN && get_visible() && mouse_over_ele > -1)  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 21;
		var.num = mouse_over_ele;
        do_callback(&var);
    }
	//Ueber welchem teilbutton ist der Mauszeiger?
	if( what==SDL_MOUSEMOTION && x>0 && x<get_w() )
	{
		bool tmp=0;
			for(int i=0; i<elements.size(); i++)
			{
				if(y>(5+fontspace+i*(fontheight+fontspace)) && y<(i*fontspace+5+(i+1)*fontheight+fontheight) )
				{
					mouse_over_ele = i;
					tmp=1;
				}
			}
		if(!tmp) mouse_over_ele = -1;
	}
	else
	{
		mouse_over_ele = -1;
	}
	
    uv_widget::mouse_action(x,y,button,what);
	//Verschwinden lassen wenn irgendwo geklickt
	if(what == SDL_MOUSEBUTTONDOWN && mouse_over()){
		set_visible(0);
		return true;
	}
		
	return false;
}
//---------------------------------------------------------------------------
bool uv_list::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 11;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
