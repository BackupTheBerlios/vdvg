//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_group.h"
//---------------------------------------------------------------------------
uv_widget::uv_widget(int mx, int my, int mw, int mh,uv_group *parent,
                     char *mlabel, bool CanFocusHave)
{
   x=mx; y=my; w=mw; h=mh; myparent=parent; label=mlabel; visible=1;
   callback=NULL; can_focus_have=CanFocusHave;
   //Das Child beim Parent eintragen (wenn parent != 0)
   if(parent!=0)
      myparent->add_child(this);
};
//---------------------------------------------------------------------------
int uv_widget::get_absolute_x()
{
    if(myparent)
        return (myparent->get_absolute_x()+get_x());
    return 0;
};
//---------------------------------------------------------------------------
int uv_widget::get_absolute_y()
{
    if(myparent)
        return (myparent->get_absolute_y()+get_y());
    return 0;
};
//---------------------------------------------------------------------------
void uv_widget::set_parent(uv_group *parent)
{
   //Hier muss sich, wenn myparent != 0, das child noch abmelden
   myparent=parent;
   myparent->add_child(this);
}
//---------------------------------------------------------------------------
