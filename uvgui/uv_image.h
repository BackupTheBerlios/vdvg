//---------------------------------------------------------------------------
#ifndef _UV_DRAW_IMG_
#define _UV_DRAW_IMG_
//---------------------------------------------------------------------------
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"  //Reihenfolge vertauschen
#include "uv_widget.h"
#include "uv_group.h"
#include <map>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class uv_image:public uv_widget
{
private:
    GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord );
    int power_of_two(int input);
    int w, h;
    GLuint textur;
    bool loaded;
    GLfloat texMinX,texMinY,texMaxX,texMaxY;
    bool initialised;
public:
    bool LoadImageFile(string fname);

    uv_image(string filename);
    uv_image();
    uv_image(int mx, int my, int mw, int mh, uv_group *parent, char *label=0);


    void set_texcoordinaten(float x, float y, float mx, float my)
    {
       texMinX = x; texMinY = y; texMaxX = mx; texMaxY = my;
    };
    GLuint get_texture_index()
    {
        return textur;
    };
    int get_texture_w()
    {
        return w;
    };
    int get_texture_h()
    {
        return h;
    };
    bool is_texture_successfully_loaded()
    {
        return loaded;
    };
    void draw_size(int x, int y, int w, int h,
                   float picx=-1, float picy=-1, float picw=-1, float pich=-1);
    void draw_original_size(int x, int y)
    {
        draw_size(x, y, get_texture_w(), get_texture_h());
    };
    void draw()
    {
       draw_size(get_absolute_x(),get_absolute_y(), get_w(), get_h());
    };
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
