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
#include "uv_container.h"
//---------------------------------------------------------------------------
void uv_container::draw(vector<GLuint> * clist)
{
   if(get_visible()) draw_childs(clist);
}
//---------------------------------------------------------------------------
uv_container::attribute uv_container::make_attribut(uv_group * parent)
{
attribute tmp;
tmp.parent = parent;
return tmp;
}

bool uv_container::initialize(attribute atr)
{
 uv_group::initialize(uv_group::make_attribut(atr.parent,0,0,1600,1400,"",0));
 return 1;
};

bool uv_container::key_action(int key, int sym, int mod, int what)
{
   if(get_visible()) key_action_childs(key, sym, mod, what);
}

bool uv_container::mouse_action(int x, int y, int button, int what)
{	
    if(what==SDL_MOUSEBUTTONDOWN && get_visible())
   {
      get_parent()->set_focus(this);
   }

    if(get_visible()) return mouse_action_childs(x, y, button, what);
    return 1;
}

void uv_container::mouse_move_rel(int rel_x, int rel_y)
{
    if(get_visible()) mouse_move_rel_childs(rel_x, rel_y);
}

