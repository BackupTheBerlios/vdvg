#include "uv_window.h"

uv_window::uv_window(int mx, int my, int width, int height, uv_group *parent, char *label):uv_group(mx,my,width,height,parent,label)
{
    parent->add_child(this);
    dragged = 0;
}

void uv_window::draw()
{
    if(!get_visible()) return;
    //Eigenes Fenster zeichnen...
    glBegin (GL_QUADS);
    glColor3ub (200, 200, 0);
    glVertex2i (get_absolute_x(), get_absolute_y());
    glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
    glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
    glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
    glEnd ();

    uv_widget *child;
    set_start_child();
    while((child=get_next_child()) && child != NULL)
    {
        child->draw();
    }
}

void uv_window::mouse_action(int x, int y, int button, int what)
{
    if(y < 20 && what==SDL_MOUSEBUTTONDOWN ) dragged=1;//Mausklick im Drag Bereich
    if(what==SDL_MOUSEBUTTONUP) dragged=0;

    uv_widget *child;
    set_start_child();
    while((child=get_next_child()) && child != NULL)
    {
        if(child->get_x() < x &&
                child->get_y() < y &&
                (child->get_x() + child->get_w()) > x &&
                (child->get_y() + child->get_h()) > y)
        {
            child->mouse_action(x - (child->get_x()),y - (child->get_y()),button,what);
        }
    }
}

void uv_window::key_action(int key, int mod, int what)
{

}

void uv_window::mouse_move_rel(int rel_x, int rel_y)
{
    if(dragged)
    {
        set_pos(get_x()+rel_x,get_y()+rel_y);
        //set_pos(rel_x,rel_y);
    }
}
