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
// File:       uv_gui.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#include "uv_gui.h"
//---------------------------------------------------------------------------
//Diese Source Datei beinhaltet einige Zeiger und globale Funktionen...
//---------------------------------------------------------------------------
static int mouse_x;	 //aktuelle Maus x- Koordinate
static int mouse_y;	 //aktuelle Maus y- Koordinate
//---------------------------------------------------------------------------
int get_mouse_x()
{
    return mouse_x;
};
//---------------------------------------------------------------------------
int get_mouse_y()
{
    return mouse_y;
};
//---------------------------------------------------------------------------
void set_mouse_x(int x)
{
    mouse_x=x;
};
//---------------------------------------------------------------------------
void set_mouse_y(int y)
{
    mouse_y=y;
};
//---------------------------------------------------------------------------
int rel_mouse_x(int x)
{
    static int old_x = x;
    int rel = x-old_x;
    old_x = x;
    return rel;
};
//---------------------------------------------------------------------------
int rel_mouse_y(int y)
{
    static int old_y = y;
    int rel = y-old_y;
    old_y = y;
    return rel;
};
//---------------------------------------------------------------------------

