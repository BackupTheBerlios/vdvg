//---------------------------------------------------------------------------
#include "uv_imagebox.h"
//---------------------------------------------------------------------------
uv_imagebox::uv_imagebox(int mx, int my, int mw, int mh,
                         uv_group *parent, string file)
                         :uv_widget(mx, my, mw, mh, parent, 0)
{
   parent->add_child(this); //sich beim Parent eintragen
   tex.LoadImageFile(file); //Textur laden
   //ntext.init("Test.ttf", 30);
   //ntext.set_color(0,0,0);

};
//---------------------------------------------------------------------------
void uv_imagebox::draw()
{
   tex.draw_size(get_absolute_x(), get_absolute_y(), get_w(), get_h());
   //ntext.print(get_absolute_x()+10, get_absolute_y()+10, "Hallo Welt!\n\nDies ist ein Test des Text Interface!\n\nBenny");
};
//---------------------------------------------------------------------------
