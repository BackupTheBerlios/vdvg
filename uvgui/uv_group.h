#ifndef _UV_GROUP_
#define _UV_GROUP_

#include "uv_widget.h"
#include <vector>	//Childs speichern
using namespace std;

/*! @class uv_group
 *  @brief Verwaltet gemeinsame Optionen fuer alle Widgets mit Childs
 *  @author Lukas H
 *  @version 1.0
 *
 *  Diese Klasse enthält funktionen, die die Verwaltung von Childs unterstuetzen.
 */

class uv_group:public uv_widget
{
private:
    vector < uv_widget * >childs;	// Beinhaltet alle Child widgets...
    vector < uv_widget * >::iterator ite;  //Iterator, der an der aktuellen Pos steht
public:
    uv_group(int mx, int my, int mw, int mh,uv_group *parent=0, char *mlabel=0);
    uv_widget* get_next_child();
    void set_start_child();		//Iterator == 0
    void mouse_move_rel(int rel_x, int rel_y);
    void add_child(uv_widget* );
};


#endif
