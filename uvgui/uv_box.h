#ifndef _UV_BOX_
#define _UV_BOX_

#include "SDL.h"
#include "SDL_opengl.h"
#include "uv_widget.h"
#include "uv_group.h"

class uv_box:public uv_widget
{
	private:
		GLubyte red,green,blue;
	public:
		void draw();
		uv_box(int x, int y, int w, int h, uv_group *parent);
		uv_box();
		void set_color(GLubyte red,GLubyte green, GLubyte blue)
		{
			this->red=red;
			this->green=green;
			this->blue=blue;
		}
	
	
};


#endif
