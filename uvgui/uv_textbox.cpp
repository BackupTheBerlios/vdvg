//---------------------------------------------------------------------------
// File:       uv_textbox.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_textbox.h"
//---------------------------------------------------------------------------
uv_textbox::uv_textbox(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel)
                       : uv_group(mx,my,mw,mh,parent,mlabel),
                         text(0, 0, 0, 0, this, "Textbox")
{
    text.init("Franklin-Italic.ttf",16);
    text.set_color(0,0,0);
    //text.text << mlabel;
    text.pushtext(mlabel);
    //Den Text in der Textbox positionieren
    text.set_pos(5,((get_h()+text.get_height())/2)-2);
    for(int i=0; i<256; i++) str[i]=0;
    pos = 0;

    this->parent=parent;

    //Display-Listen Zeugs:
    if(!(stranslation = glGenLists(5)))
       return; //Error !!
    drawing = stranslation+1;
    etranslation = drawing+1;
    scissoran = etranslation+1;
    scissoraus = scissoran+1;

    redraw = true;
    retranslate = true;
};
//---------------------------------------------------------------------------
void uv_textbox::draw(basic_string<GLuint> * clist)
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
   };

   if(redraw)
   {
      glNewList(drawing, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, 0);
      glBegin (GL_QUADS);
         glColor3ub(255, 255, 255);
         // Links Oben
         glVertex2i (0, 0);
         // Rechts Oben
         glVertex2i (get_w (), 0);
         // Rechts Unten
         glVertex2i (get_w (), get_h ());
         // Links Unten
         glVertex2i (0, get_h ());
      glEnd ();
      glEndList();

      redraw = false;
   };

   if(true)
   {
      glNewList(scissoran, GL_COMPILE);
      // Nutze Scissor Testing f�r das clipping des Textes:
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport); //Bildschirmgr�sse abholen
      int hight = viewport[3]; //Bildschirmh�he
      // Definiere die  Scissor Region
      glScissor(get_absolute_x()+5, hight-get_absolute_y()-get_h()+1,
      get_w()-10, get_h()-2);//hight-get_h()+2);
      // aktiviere Scissor Testing
      glEnable(GL_SCISSOR_TEST);
      glEndList();

      glNewList(scissoraus, GL_COMPILE);
      // deaktiviere Scissor Testing
      glDisable(GL_SCISSOR_TEST);
      glEndList();
   }

   clist->push_back(stranslation);
   clist->push_back(drawing);

   clist->push_back(scissoran);

   //Die childs zeichnen:
   draw_childs(clist);

   clist->push_back(scissoraus);

   clist->push_back(etranslation);
};
//---------------------------------------------------------------------------
void uv_textbox::key_action(int key, int sym, int mod, int what)
{
   if(SDL_KEYDOWN == what)
   {
      if(key == SDLK_RSHIFT)     return;
      if(key == SDLK_LSHIFT)     return;
      if(key == SDLK_CAPSLOCK)   return;
      if(key == SDLK_NUMLOCK)    return;
      if(key == SDLK_SCROLLOCK)  return;
      if(key == SDLK_LCTRL)      return;
      if(key == SDLK_RCTRL)      return;
      if(key == SDLK_RALT)       return;
      if(key == SDLK_LALT)       return;

      //Ist es ein Buchstaben ?
      if(key >= 97 && key <= 122)
      {
         str.insert(pos++, 1, key);
      }
      //sonst ein anderes Zeichen:
      else
      {
         switch(sym)
         {
            case SDLK_DELETE:
               if(pos >= str.length())
                  break;
               str.erase(pos, 1);
               break;
            case SDLK_LEFT:
               if(pos==0)
                  break;
               --pos;
               break;
            case SDLK_RIGHT:
               if(pos >= str.length())
                  break;
               ++pos;
               break;
            case SDLK_HOME:
               pos=0;
               break;
            case SDLK_END:
               pos=str.length();
               break;
            default:
               switch(key)
               {
                  case SDLK_BACKSPACE:
                     if(pos==0)
                        break;
                     str.erase(--pos, 1);
                     break;
                  default:
                     if(key == 0)
                        break;
                     str.insert(pos++, 1, key);
                     break;
               }; //switch(key)
         };//switch(sym)
      };
   }
   text.pushtext(str);
};
//---------------------------------------------------------------------------
bool uv_textbox::mouse_action(int x, int y,int button,int what)
{
   if(what==SDL_MOUSEBUTTONDOWN && get_visible())
   {
      parent->set_focus(this);
   }
   uv_widget::mouse_action(x,y,button,what);
   return true;
}
//---------------------------------------------------------------------------
