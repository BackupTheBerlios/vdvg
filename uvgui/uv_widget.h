//---------------------------------------------------------------------------
// File:       uv_widget.h
// Created by: Lukas Hubmel <luki@humbels.com>
// Created on: Tue Apr 13 00:07:11 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_WIDGET_H_
#define _UV_WIDGET_H_
//---------------------------------------------------------------------------
class uv_group;  //forward-Deklaration von uv_group
//---------------------------------------------------------------------------
#include "uv_gui.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
using namespace std;

typedef void (*voidcallback)();
//-------------------------------------------------------------------------//
//  @class uv_widget                                                       //
//  @brief Verwaltet gemeinsame Optionen eines Widgets                     //
//  @author Lukas H                                                        //
//  @version 1.0                                                           //
//                                                                         //
//  Basisklasse für alle Widgets, enthält Virtuelle Funktionen             //
//                                                                         //
//-------------------------------------------------------------------------//
class uv_widget
{
   private:
      int x, y, w, h;
      voidcallback callback;
      int whenbits;
      char *label;
      bool visible;
      uv_group *myparent;
      bool can_focus_have;  //Kann das Widget den Focus bekommen?
      bool mouseover;

   public:
      //setzt Variabeln,Konstruktor, sollte irgendwie protected sein...
      uv_widget(int x, int y, int width, int height,uv_group *parent=0,
                char *label=0, bool CanFocusHave=false);

      //Destruktor
      virtual ~uv_widget(); //Macht nichts

      uv_group* get_parent(); //Liefert einen Zeiger auf den Parent zurück
      void set_parent(uv_group *parent); //Setze den Zeiger auf den Parent

      int get_w(); //Liefert die breite (width)
      int get_h(); //Liefert die Hoehe (height)
      int get_x(); //Liefert die relative x-Koordinate
      int get_y(); //Liefert die relative y-Koordinate

      int get_absolute_x(); //Liefert die absolute x-Koordinate
      int get_absolute_y(); //Liefert die absolute y-Koordinate

      //Die Position eines Widgets setzen
      void set_pos(int x, int y);
      //Grösse und Position eines Widgets verändern/setzen
      bool set_size(int x, int y, int width, int height);

      virtual void draw(basic_string<GLuint> * clist)=0; //Zeichnet das Widget

      //Setz einen Funktionszeiger für Callback
      void set_callback(voidcallback callback);
      //Callback Adresse zurückgeben
      voidcallback get_callback();
      void do_callback();
      void set_when(int bitset); //Wann wird der Callback ausgelöst?

      char* get_label();      //Label zurueckgeben

      void set_visible(bool visible);  //wenn visible=0, nicht zeichnen
      bool get_visible(); //visible?

      bool kann_focus_haben();
      bool mouse_over();

      //key=Taste, mod=Modifiers, what=UP,Down
      virtual void key_action(int key, int sym, int mod, int what);
      virtual bool mouse_action(int x, int y,int button,int what);
      virtual void mouse_move_rel(int rel_x, int rel_y);
      virtual void set_mouse_over_off();
};
//---------------------------------------------------------------------------
#endif	//_UVWIDGET_H_
//---------------------------------------------------------------------------
