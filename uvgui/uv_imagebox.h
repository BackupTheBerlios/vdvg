#ifndef _UV_IMAGEBOX_H_
#define _UV_IMAGEBOX_H_

#include "uv_texture.h"
#include "uv_window.h"

class uv_imagebox:public uv_widget
{
private:
    uv_texture tex;
public:
    void draw();
    uv_imagebox(int mx, int my, int mw, int mh,uv_group *parent=0, string file="");
};

#endif
