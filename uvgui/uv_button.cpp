//---------------------------------------------------------------------------
// File:       uv_button.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_button.h"
//---------------------------------------------------------------------------
uv_button::uv_button():uv_group(0,0,0,0,0,"")
{
    //Display-Listen Zeugs:
    if(!(stranslation = glGenLists(4)))
       return; //Error !!
    drawing1 = stranslation+1;
    drawing2 = drawing1+1;
    etranslation = drawing2+1;

    redraw = true;
    retranslate = true;
}
//---------------------------------------------------------------------------
bool uv_button::initialize(attribute init)
{
   set_parent(init.parent);
   set_size(init.x, init.y, init.width, init.height);

   uv_color text_color = {0xff, 0x88, 0x00};
   text = uv_text::make_attribut(this, 0, 0, 0, 0, 25, "Buttontext", init.caption, "Test.ttf", text_color);
   text.set_pos((get_w()-text.get_width())/2, (get_h()+text.get_height())/2);

   redraw = true;
   retranslate = true;

   return true;
};
//---------------------------------------------------------------------------
uv_button::attribute uv_button::make_attribut(uv_group * parent,
                                              int x, int y, int width, int height,
                                              string name, string caption)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.name = name; attr.caption = caption;

   return attr;
};
//---------------------------------------------------------------------------
void uv_button::draw(basic_string<GLuint> * clist)
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
      glNewList(drawing1, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, 0);
      glBegin (GL_QUADS);
         glColor3ub (100, 100, 100);
         glVertex2i (0, 0);             // Links Oben
         glVertex2i (get_w(), 0);       // Rechts Oben
         glColor3ub (255, 255, 255);
         glVertex2i (get_w(), get_h()); // Rechts Unten
         glVertex2i (0, get_h());       // Links Unten
      glEnd ();
      glEndList();

      glNewList(drawing2, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, 0);
      glBegin (GL_QUADS);
         glColor3ub (150, 150, 150);
         glVertex2i (0, 0);             // Links Oben
         glVertex2i (get_w(), 0);       // Rechts Oben
         glColor3ub (255, 255, 255);
         glVertex2i (get_w(), get_h()); // Rechts Unten
         glVertex2i (0, get_h());       // Links Unten
      glEnd ();
      glEndList();

      redraw = false;
   }

   clist->push_back(stranslation);
   if(!mouse_over())
      clist->push_back(drawing1);
   else
      clist->push_back(drawing2);

   draw_childs(clist);

   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
bool uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 11;
        do_callback(&var);
    }
    uv_widget::mouse_action(x,y,button,what);
    return true;
}
//---------------------------------------------------------------------------
void uv_button::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 11;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
