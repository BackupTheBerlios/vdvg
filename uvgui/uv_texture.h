#ifndef _UV_DRAW_IMG_
#define _UV_DRAW_IMG_

#include "SDL_opengl.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class uv_texture
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

    uv_texture(string filename);
    uv_texture();

    GLuint get_texture_index()
    {return textur;}
    int get_texture_w()
    {return w;}
    int get_texture_h()
    {return h;}
    bool is_texture_successfully_loaded()
    {return loaded;}
    void draw_size(int x, int y, int w, int h);
    void draw_original_size(int x, int y)
    {draw_size(x, y, get_texture_w(), get_texture_h());}

};


#endif
