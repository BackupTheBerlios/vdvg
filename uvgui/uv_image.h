//---------------------------------------------------------------------------
// File:       uv_image.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_DRAW_IMG_
#define _UV_DRAW_IMG_
//---------------------------------------------------------------------------
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"  //Reihenfolge vertauschen
#include "uv_widget.h"
#include "uv_group.h"
//#include "uv_include.h"
#include <map>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class uv_image:public uv_widget
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      string name, image;
      float picx, picy, picw, pich;
   };
   struct callback: public uv_callback
   {

   };
private:
    //Variabeln:
    int w, h;
    GLuint textur;
    bool loaded;
    GLfloat texMinX,texMinY,texMaxX,texMaxY;
    bool initialised;

    GLuint stranslation, etranslation, drawing;
    bool redraw, retranslate;

    float picx, picy, picw, pich;

    //Funktionen:
    int power_of_two(int input);
    GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord );
    void draw_size(int x, int y, int w, int h,
                   float picx=-1, float picy=-1, float picw=-1, float pich=-1);

public:
//    uv_image(int mx, int my, int mw, int mh, uv_group *parent, char *label=0);
    uv_image();

    bool initialize(attribute init);
    bool operator=(attribute init) {return initialize(init);};

    static attribute make_attribut(uv_group * parent,
                            int x, int y, int width, int height,
                            string name, string image,
                            float picx=0.0, float picy=0.0, float picw=1.0, float pich=1.0);

    bool LoadImageFile(string fname);

    GLfloat get_texMinX();
    GLfloat get_texMinY();
    GLfloat get_texMaxX();
    GLfloat get_texMaxY();

    void set_texcoordinaten(float x, float y, float mx, float my);
    GLuint get_texture_index();
    int get_texture_w();
    int get_texture_h();
    bool is_texture_successfully_loaded();

    bool set_size(int x, int y, int w=-1, int h=-1,
                  float picx=-1, float picy=-1, float picw=-1, float pich=-1);
    void draw(basic_string<GLuint> * clist);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
