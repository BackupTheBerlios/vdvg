#include "uv_button.h"

uv_button::uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel):uv_group(mx,my,mw,mh,parent,mlabel)
{
    text.set_parent(this);
    text.init("Test.ttf",20);
    text.set_color(0xff,0x88,0x00);
    text.text << mlabel;
    //Den Text auf dem Button zentrieren
    text.set_pos((get_w()-text.get_width())/2,(get_h()-text.get_height())/2);
    //cout << "Höhe: "<< text.get_height()<<endl;
    //cout << "Breite: "<< text.get_width()<<endl;
}

void uv_button::draw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    if(get_visible())
    {
        glBegin (GL_QUADS);
        // Links Oben
        if( mouse_over() ) glColor3ub (150, 150, 150);
        else glColor3ub (100, 100, 100);
        //glColor3ub(255, 0, 0);
        glVertex2i (get_absolute_x(), get_absolute_y());
        // Rechts Oben
        //glColor3ub (0, 255, 0);
        glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
        // Rechts Unten
        glColor3ub (255, 255, 255);
        //glColor3ub(255, 0, 0);

        glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
        // Links Unten
        //glColor3ub (255, 255, 0);
        glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
        glEnd ();

        draw_childs();
    }
}

bool uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        do_callback();
    }
    return true;
}

void uv_button::key_action(int key, int mod, int what)
{
   if(key == SDLK_RETURN)//key == SDLK_RETURN)
      do_callback();
}
