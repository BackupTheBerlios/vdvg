//---------------------------------------------------------------------------
// File:       uv_group.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_GROUP_
#define _UV_GROUP_
//---------------------------------------------------------------------------
#include "uv_widget.h"
#include "uv_array.h"
#include <vector>	//Childs speichern

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
/*! @class uv_group
 *  @brief Verwaltet gemeinsame Optionen fuer alle Widgets mit Childs
 *  @author Lukas H
 *  @version 1.0
 *
 *  Diese Klasse enthÃ¤lt funktionen, die die Verwaltung von Childs unterstuetzen.
 */
//---------------------------------------------------------------------------
class uv_group:public uv_widget
{
private:
    dstack<uv_widget *> childs;
    bool next_child;
    bool last_child;
public:
    uv_group(int mx, int my, int mw, int mh,uv_group *parent=0, char *mlabel=0, bool CanHaveFocus=false);
    uv_widget* get_next_child();
    uv_widget* get_last_child();
    void set_start_child(); 		//Iterator == 0
    void set_end_child();
    void mouse_move_rel(int rel_x, int rel_y);
    void add_child(uv_widget*);
    void remove_child(uv_widget* widget);
    void add_child_in_front(uv_widget* );
    void set_to_end();
    bool draw_childs(basic_string<GLuint> * clist);
    bool mouse_action_childs(int x, int y, int button, int what);
    bool key_action_childs(int key, int sym, int mod, int what);
    bool mouse_move_rel_childs(int rel_x, int rel_y);
	void set_mouse_over_off();
    bool set_focus(uv_widget * widgetpointer);
    bool set_in_front(uv_widget * widgetpointer);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
