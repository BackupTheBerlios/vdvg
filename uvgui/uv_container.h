/*
-----------------------------------------------------------------------------
4D 4Gewinnt is simple board game.
Copyright (C) 2004 Benny Loeffel, Lukas Humbel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
-----------------------------------------------------------------------------
*/
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

