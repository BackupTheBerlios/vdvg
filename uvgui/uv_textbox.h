//---------------------------------------------------------------------------
#ifndef uv_textboxH
#define uv_textboxH
//---------------------------------------------------------------------------
#include "uv_group.h"
#include "uv_text.h"
//---------------------------------------------------------------------------
class uv_textbox: public uv_group
{
   private:
      uv_text text;
      char str2[256];
      string str;
      string::iterator iter;
      int pos;
   public:
      uv_textbox(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel=0);
      void draw();
      //bool mouse_action(int x, int y, int button, int what);
      void key_action(int key, int sym, int mod, int what);
};
//---------------------------------------------------------------------------
#endif
 