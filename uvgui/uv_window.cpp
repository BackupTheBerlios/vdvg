//---------------------------------------------------------------------------
#include "uv_window.h"
//---------------------------------------------------------------------------
uv_window::uv_window(int mx, int my, int width, int height,
                     uv_group *parent, char *label)
                     :uv_group(mx, my, width, height, parent, label, true)
                      , oben(0, 0, get_w(), 20, this, "Test.bmp")
{
    parent->add_child(this);  //Sollte eigentlich in uv_widget
    dragged = 0;
};
//---------------------------------------------------------------------------
void uv_window::draw()
{
    if(!get_visible()) return;
    //Eigenes Fenster zeichnen...
    glBegin (GL_QUADS);
    //glColor3ub (0, 0, 255);
    glColor4ub(0, 0, 255, 100);
    glVertex2i (get_absolute_x(), get_absolute_y());
    glVertex2i (get_absolute_x() + get_w (), get_absolute_y());
    glVertex2i (get_absolute_x() + get_w (), get_absolute_y() + get_h ());
    glVertex2i (get_absolute_x(), get_absolute_y() + get_h ());

    //glColor3ub (200, 200, 0);
    glColor4ub(200, 200, 0, 100);
    glVertex2i (get_absolute_x()+2,         get_absolute_y()+20);
    glVertex2i (get_absolute_x()+get_w()-2, get_absolute_y()+20);
    glVertex2i (get_absolute_x()+get_w()-2, get_absolute_y()+get_h()-2);
    glVertex2i (get_absolute_x()+2,         get_absolute_y()+get_h()-2);
    glEnd ();

    //Alle Childs zeichnen
    draw_childs();
};
//---------------------------------------------------------------------------
bool uv_window::mouse_action(int x, int y, int button, int what)
{
    if(y < 20 && what==SDL_MOUSEBUTTONDOWN)
        dragged=true; //Mausklick im Drag Bereich
    if(what==SDL_MOUSEBUTTONUP)
        dragged=false;

    return mouse_action_childs(x, y, button, what);
};
//---------------------------------------------------------------------------
void uv_window::key_action(int key, int mod, int what)
{

};
//---------------------------------------------------------------------------
void uv_window::mouse_move_rel(int rel_x, int rel_y)
{
    if(dragged)
    {
        set_pos(get_x()+rel_x,get_y()+rel_y);
    }

    mouse_move_rel_childs(rel_x, rel_y);
};
//---------------------------------------------------------------------------

