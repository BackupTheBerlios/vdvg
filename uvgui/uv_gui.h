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

