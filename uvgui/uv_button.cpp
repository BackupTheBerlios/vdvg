#include "uv_button.h"

uv_button::uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel):uv_widget(mx,my,mw,mh,parent,mlabel)
{
    parent->add_child(this);
    text.init("Test.ttf",16);

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

        //kommt noch in die Text Klasse
        glColor3ub(0xff,0,0);
        //glRasterPos2f(50.0f, 50.0f);
        text.print(get_absolute_x(),750-get_absolute_y(),get_label());
        //sehr, sehr, sehr unschˆn...
        glColor3ub(0xff,0xff,0xff);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
}

bool uv_button::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN)
    {
        //static int ms_last_called=0;
        //if(SDL_GetTicks()-ms_last_called > 250)	//Das sollte eigentlich irgendwie sch√∂ner gehen..
        //{
        do_callback();
        //ms_last_called=SDL_GetTicks();
    }
}

void uv_button::key_action(int key, int mod, int what)
{

}
