#ifndef _UV_BUTTON_
#define _UV_BUTTON_

#include "uv_widget.h"
#include "uv_group.h"
#include <SDL_opengl.h>
#include <SDL.h>

/*! @class uv_button
 *  @brief Erstellt ein anklickbaren Button
 *  @author Lukas H
 *  @version 1.0
 *
 */
class uv_button:public uv_widget
{
private:

public:
    uv_button(int mx, int my,int mw,int mh, uv_group *parent, char *mlabel=0);
    void draw();
    void mouse_action(int x, int y, int button, int what);
    void key_action(int key, int mod, int what);
};

#endif
