//---------------------------------------------------------------------------
#include "uv_button.h"
//---------------------------------------------------------------------------
uv_button::uv_button(int mx, int my,int mw,int mh,
                     uv_group *parent, char *mlabel)
                     :uv_widget(mx,my,mw,mh,parent,mlabel)
{
   parent->add_child(this);
   tex.LoadImageFile("Beenden.bmp");
}
//---------------------------------------------------------------------------
//Den Button zeichnen
void uv_button::draw()
{
   if(get_visible()) //Auf Sichtbarkeit prüfen
   {
      tex.draw_size(get_absolute_x(), get_absolute_y(), get_w(), get_h());
      /*glBegin(GL_QUADS);
         // Oben
         if(mouse_over())
            glColor3ub(150, 150, 150);
         else
            glColor3ub(100, 100, 100);
         //   "   Links
         glVertex2i(get_absolute_x(), get_absolute_y());
         //   "   Rechts
         glVertex2i(get_absolute_x () + get_w (), get_absolute_y());

         // Unten
         glColor3ub(255, 255, 255);
         //   "   Rechts
         glVertex2i(get_absolute_x()+get_w(), get_absolute_y()+get_h());
         //   "   Links
         glVertex2i(get_absolute_x(), get_absolute_y()+get_h());
      glEnd();*/
   }
};
//---------------------------------------------------------------------------
bool uv_button::mouse_action(int x, int y,int button,int what)
{
   if(what==SDL_MOUSEBUTTONDOWN)
   {
      //Die Callback-Funktion aufrufen:
      do_callback();
   }
   return true;
};
//---------------------------------------------------------------------------
void uv_button::key_action(int key, int mod, int what)
{

};
//---------------------------------------------------------------------------
