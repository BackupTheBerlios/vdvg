//---------------------------------------------------------------------------
#ifndef _UV_DRAW_IMG_
#define _UV_DRAW_IMG_
//---------------------------------------------------------------------------
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"  //Reihenfolge vertauschen
#include "uv_widget.h"
#include "uv_group.h"


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
public:
    bool LoadImageFile(string fname);

    uv_image(string filename);
    uv_image();
	uv_image(int mx, int my, int mw, int mh, uv_group *parent, char *label=0);

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
    void draw_size(int x, int y, int w, int h);
    void draw_original_size(int x, int y)
    {
        draw_size(x, y, get_texture_w(), get_texture_h());
    };
	void draw()
	{
		draw_original_size(get_x(),get_y());
	};
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
