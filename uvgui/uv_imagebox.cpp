//---------------------------------------------------------------------------
#include "uv_imagebox.h"
//---------------------------------------------------------------------------
uv_imagebox::uv_imagebox(int mx, int my, int mw, int mh,
                         uv_group *parent, string file)
        :uv_widget(mx, my, mw, mh, parent, 0)
{
    parent->add_child(this); //sich beim Parent eintragen
    tex.LoadImageFile(file); //Textur laden
};
//---------------------------------------------------------------------------
void uv_imagebox::draw()
{
    tex.draw_size(get_absolute_x(), get_absolute_y(), get_w(), get_h());
};
//---------------------------------------------------------------------------

