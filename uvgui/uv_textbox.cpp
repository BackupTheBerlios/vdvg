//---------------------------------------------------------------------------
// File:       uv_textbox.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
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
    //Den Text auf dem Button zentrieren
    text.set_pos(5,((get_h()-text.get_height())/2)-2);
    for(int i=0; i<256; i++) str[i]=0;
    iter = str.end();
    pos = 0;
};
//---------------------------------------------------------------------------
void uv_textbox::draw()
{
   glBindTexture(GL_TEXTURE_2D, 0);
   if(get_visible())
   {
      glBegin (GL_QUADS);
         glColor3ub(255, 255, 255);
         // Links Oben
         glVertex2i (get_absolute_x(), get_absolute_y());
         // Rechts Oben
         glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
         // Rechts Unten
         glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
         // Links Unten
         glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
      glEnd ();
      
      draw_childs();
   }
}
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
         str.insert(iter, key);
         iter = &str[++pos];
         //str += key;
      }
      //sonst ein anderes Zeichen:
      else
      {
         switch(sym)
         {
            case SDLK_DELETE:
               if(pos >= str.length())
                  break;
               str.erase(iter);
               iter = &str[pos];
               break;
            case SDLK_LEFT:
               if(pos==0)
                  break;
               iter = &str[--pos];
               break;
            case SDLK_RIGHT:
               if(pos >= str.length())
                  break;
               iter = &str[++pos];
               break;
            case SDLK_HOME:
               iter = &str[(pos=0)];
               break;
            case SDLK_END:
               iter = &str[(pos=str.length())];
               break;
            default:
               switch(key)
               {
                  case SDLK_BACKSPACE:
                     //str.pop_back();
                     if(pos==0)
                        break;
                     iter = &str[--pos];
                     str.erase(iter);
                     break;
                  default:
                     if(key == 0)
                        break;
                     str.insert(iter, key);
                     iter = &str[++pos];
                     //str += key;
                     break;
               }; //switch(key)
         };//switch(sym)
      };
   }

   text.pushtext(str);
};
//---------------------------------------------------------------------------
