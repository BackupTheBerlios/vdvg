//---------------------------------------------------------------------------
#ifndef UV_CONTAINER
#define UV_CONTAINER
//---------------------------------------------------------------------------
#include "uv_group.h"
//---------------------------------------------------------------------------
class uv_container : public uv_group
{
   private:
   public:
      struct attribute
 		{
		 uv_group * parent;
		};
      static attribute make_attribut(uv_group *parent);
      void draw(vector<GLuint> * clist);
      bool key_action(int key, int sym, int mod, int what);
      bool mouse_action(int x, int y, int key, int what);
      void mouse_move_rel(int rel_x, int rel_y);
		bool operator=(attribute atr) {return initialize(atr);};
		bool initialize(attribute atr);
		
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

