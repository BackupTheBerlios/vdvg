//---------------------------------------------------------------------------
// File: uvwidget.h
// Created by: User <Email>
// Created on: Tue Apr 13 00:07:11 2004
//---------------------------------------------------------------------------
#ifndef _UV_WIDGET_H_
#define _UV_WIDGET_H_
//---------------------------------------------------------------------------
class uv_group;
//---------------------------------------------------------------------------
#include "uv_gui.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <iostream>
//---------------------------------------------------------------------------
using namespace std;

typedef void (*voidcallback)();
//---------------------------------------------------------------------------
/*! @class uv_widget
 *  @brief Verwaltet gemeinsame Optionen eines Widgets
 *  @author Lukas H
 *  @version 1.0
 *
 *  Basisklasse für alle Widgets, enthält Virtuelle Funktionen
 */
//---------------------------------------------------------------------------
class uv_widget
{
private:
    int x,y,w,h;
    voidcallback callback;
    int whenbits;
    char *label;
    bool visible;
    uv_group *myparent;
    bool can_focus_have;  //Kann das Widget den Focus bekommen?
	bool mouseover;
public:
    //setzt Variabeln,Konstruktor, sollte irgendwie protected sein...
    uv_widget(int mx, int my, int mw, int mh,uv_group *parent=0,
              char *mlabel=0, bool CanFocusHave=false);

    virtual ~uv_widget() //Macht nichts
    {

    };
    uv_group* get_parent()
    {
        return myparent;
    };
    void set_parent(uv_group *parent);

	
    int get_w()   //Liefert die breite (width)
    {
        return w;
    };
    int get_h()   //Liefert die Hoehe (height)
    {
        return h;
    };
    int get_x()   //Liefert die relative x Koordinate
    {
        return x;
    };
    int get_y()   //Liefert die relative y Koordinate
    {
        return y;
    };
    int get_absolute_x();
    int get_absolute_y();
    void set_pos(int mx, int my)
    {
        x = mx;
        y = my;
    };
    bool set_size(int mx, int my, int mw, int mh) //Grösse eines Widgets verändern
    {
        x=mx; y=my; w=mw; h=mh;
        return true;
    };
    virtual void draw()=0;              //Zeichnet das Widget
    void set_callback(voidcallback cb)  //Setz einen Funktionszeiger für Callback
    {
        callback=cb;
    };
    voidcallback get_callback()         //Callback Adresse zurückgeben
    {
        return callback;
    };
    void do_callback()
    {
        if(callback) (*callback)();
    };
    void set_when(int bitset)           //Wann wird der Callback ausgelÃ¶st?
    {
        whenbits = bitset;  //Bitmasken werden ueber Defines gesetzt.
    };
    char* get_label()      //Label zurueckgeben
    {
        return label;
    };
    void set_visible(bool vis)  //wenn visible=0, nicht zeichnen
    {
        visible=vis;
    };
    bool get_visible()   //visible?
    {
        return visible;
    };
    bool kann_focus_haben()
    {
        return can_focus_have;
    };
    bool mouse_over()
    {
        return mouseover;
    };
    //key=Taste, mod=Modifiers, what=UP,Down
    virtual void key_action(int key, int sym, int mod, int what)
    {

    };
    virtual bool mouse_action(int x, int y,int button,int what)
    {
        if( what==SDL_MOUSEMOTION ) mouseover = 1;
		return true;
    };
    virtual void mouse_move_rel(int rel_x, int rel_y)
    {

    };
	virtual void set_mouse_over_off()
	{
		mouseover = 0;
	}
};
//---------------------------------------------------------------------------
#endif	//_UVWIDGET_H_
//---------------------------------------------------------------------------
