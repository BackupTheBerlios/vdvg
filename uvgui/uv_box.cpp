//---------------------------------------------------------------------------
// File:       uv_box.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#include "uv_box.h"

uv_box::uv_box(int mx, int my, int mw, int mh, uv_group *parent):uv_widget(mx, my, mw,mh,parent,0)
{
	//parent->add_child(this);
	uv_box();
}

uv_box::uv_box():uv_widget(0,0,0,0,0,0)
{
	red=0xff; green=0xff; blue=0xff;
}

void uv_box::draw()
{
	glBegin (GL_QUADS);
    glColor3ub (red, green, blue);
    glVertex2i (get_absolute_x(), get_absolute_y());
    glVertex2i (get_absolute_x() + get_w (), get_absolute_y());
    glVertex2i (get_absolute_x() + get_w (), get_absolute_y() + get_h ());
    glVertex2i (get_absolute_x(), get_absolute_y() + get_h ());
	glEnd();
	glColor3ub (0,0,0);
}
