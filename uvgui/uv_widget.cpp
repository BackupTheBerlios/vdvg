//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_group.h"
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
