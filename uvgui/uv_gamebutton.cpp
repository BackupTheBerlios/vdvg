//---------------------------------------------------------------------------
// File:       uv_gamebutton.cpp
// Created by: Lukas Humbel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
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
   if(!(stranslation = glGenLists(5)))
      return false; //Error !!
   drroh = stranslation+1;
   drx   = drroh +1;
   dro   = drx+1;
   etranslation = dro+1;

   redraw = true;
   retranslate = true;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y, init.width, init.height, init.name, true));

   redraw = true;
   retranslate = true;
	
   status = 0;
   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_gamebutton::attribute uv_gamebutton::make_attribut(uv_group * parent,
                                              int x, int y, int width, int height,
                                              string name)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.name = name;

   return attr;
};
//---------------------------------------------------------------------------
void uv_gamebutton::draw(vector<GLuint> * clist)
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
      glNewList(drroh, GL_COMPILE);
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

      glNewList(drx, GL_COMPILE);
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

      glNewList(dro, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, 0);
      glBegin (GL_QUADS);
         glColor3ub (200,200, 200);
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
   clist->push_back(drroh);
   if(status == 1) clist->push_back(drx);
   if(status == 2) clist->push_back(dro);
   draw_childs(clist);

   clist->push_back(etranslation);
}
//---------------------------------------------------------------------------
bool uv_gamebutton::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 13;
		var.status = status;
        do_callback(&var);
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
      var.ID = 12;
      var.status = status;
      do_callback(&var);
   }
}
//---------------------------------------------------------------------------
