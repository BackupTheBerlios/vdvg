

#ifndef _UV_WINDOW_H_
#define _UV_WINDOW_H_

#include "uv_widget.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <vector>
#include "debug_help.h"



using namespace std;


class uv_window :  public uv_widget
{
	private:
		//Diese Funktion initialisiert SDL etc.
		void init_SDL(int breite=1024, int hoehe=768, int bit=32, uv_window *parent=0,
                          	int depth_size=24, int stencil_size=24,
                           	int doublebuffer=1, int noframe=0, char *label=0);
		//Ist das Window das root window?
		bool is_root_window;
		vector<uv_widget*> childs; //Beinhaltet alle Child widgets...
	public:
		/*uv_window(int breite=1024, int hoehe=768, uv_window *parent=0, int bit=32, 
                          	int depth_size=24, int stencil_size=24,
                           	int doublebuffer=1, int noframe=0, char *label=0);*/
		uv_window(int =1024, int =768, int =0, int =0, uv_window * =0, int =32, 
                          	int =24, int =24,
                           	int =1, int =0, char * =0);
		~uv_window();
		//Zeichne dich!
		void draw();
		//Neues Child widget hinzufügen
		void add_me(uv_widget *new_child);
		void key_action(char key);
		void mouse_action(int x, int y,int what);
};

extern void set_root_pointer(uv_window *ptr);

#endif
