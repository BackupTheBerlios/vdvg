#include "uv_button.h"

uv_button::uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel):uv_widget(mx,my,mw,mh,parent,mlabel)
{
    parent->add_child(this);

}

void uv_button::draw()
{
    if(get_visible())
    {
        glBegin (GL_QUADS);
        // Links Oben
        if( mouse_over() ) glColor3ub (150, 150, 150);
        else glColor3ub (100, 100, 100);
        glVertex2i (get_absolute_x(), get_absolute_y());
        // Rechts Oben
        //glColor3ub (0, 255, 0);
        glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
        // Rechts Unten
        glColor3ub (255, 255, 255);

        glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
        // Links Unten
        //glColor3ub (255, 255, 0);
        glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
        glEnd ();
    }
}

void uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN)
    {
        //static int ms_last_called=0;
        //if(SDL_GetTicks()-ms_last_called > 250)	//Das sollte eigentlich irgendwie schöner gehen..
        //{
        do_callback();
        //ms_last_called=SDL_GetTicks();
    }
}

void uv_button::key_action(int key, int mod, int what)
{

}
