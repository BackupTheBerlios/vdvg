#include "uv_group.h"

uv_group::uv_group(int mx, int my, int mw, int mh,uv_group *parent, char *mlabel):uv_widget(mx, my, mw, mh,parent,mlabel)
{

}

void uv_group::add_child(uv_widget *widget)
{
    childs.push_back (widget);

}

void uv_group::set_start_child()
{
    ite = childs.begin ();
}

uv_widget* uv_group::get_next_child()
{
    if(ite != childs.end())
        return *(ite++);
    else
        return NULL;

}

void uv_group::mouse_move_rel(int rel_x, int rel_y)
{
    uv_widget *child;
    set_start_child();
    while((child=get_next_child()) && child != NULL)
    {
        child->mouse_move_rel(rel_x,rel_y);
    }
}
