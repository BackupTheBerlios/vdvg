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
// File:       uv_gui.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
// File mit Globalen Funktionen
//---------------------------------------------------------------------------
#ifndef _UV_GUI_H_
#define _UV_GUI_H_
//---------------------------------------------------------------------------
//Funktionen um Mauskoordinaten zu setzen:
void set_mouse_x(int x);
void set_mouse_y(int y);
//Funktionen um Mauskoordinaten auszulesen:
int get_mouse_x();
int get_mouse_y();
//Funktionen um die relative Mausbewegung auszurechnen
int rel_mouse_x(int x);
int rel_mouse_y(int y);
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

