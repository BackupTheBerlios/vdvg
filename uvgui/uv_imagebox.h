//---------------------------------------------------------------------------
//uv_imagebox:
//Dies ist eine Box mit der man Grafiken anzeigen kann. (jpg, png usw.)
//---------------------------------------------------------------------------
#ifndef _UV_IMAGEBOX_H_
#define _UV_IMAGEBOX_H_
//---------------------------------------------------------------------------
#include "uv_texture.h"
#include "uv_window.h"
#include "uv_text.h"
//---------------------------------------------------------------------------
class uv_imagebox:public uv_widget
{
   private:
      uv_texture tex;
      //uv_text ntext;
   public:
      uv_imagebox(int mx, int my, int mw, int mh,uv_group *parent/*=0*/, string file /*=""*/);
      void draw();
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
