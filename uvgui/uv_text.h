#ifndef _UV_TEXT_
#define _UV_TEXT_


//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>


#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "uv_widget.h"
#include "uv_group.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

struct font_set
{
	const char *filename;
	unsigned int size;	
	bool operator<(const font_set &t) const
	{
		if( size < t.size ) return 1;
		if( size > t.size ) return 0;
		for(int i=0;;i++)
		{
			if( filename[i] < t.filename[i]) return 1;
			if( filename[i] > t.filename[i]) return 0;
			if( !(filename[i] && t.filename[i]) ) return 0; //Die beiden sind gleich
		}
	}
};
// Drawing routines are stolen from Nehe, Lesson 46

class uv_text:public uv_widget
{
private:
    //font_data ft_font;
    GLuint * textures;	///< Holds the texture id's
    GLuint list_base;	///< Holds the first display list id
    float h;			///< Holds the height of the font.

	vector<string> lines;	//Enthält pro Element eine Zeile vom Text...
	GLubyte red, green, blue; //Textfarbe
	void splitup();			//text -> lines
    void pop_projection_matrix();
    inline int next_p2 ( int a )	{int rval=1;while(rval<a) rval<<=1;	return rval;};
    void make_dlist ( FT_Face face, char ch, GLuint list_base, GLuint * tex_base );
    void pushScreenCoordinateMatrix();
	float len;
        bool manual;

public:
    uv_text(int mx,int my,int mw,int mh,uv_group *parent,char *label); //does currently nothing
	uv_text();
    bool init(const char * fname, unsigned int h);
	void set_color(GLubyte red,GLubyte green,GLubyte blue);
	stringstream text;
    void clean();
    void pushtext(const string str);
    void print(int x, int y);
	int get_height();
	int get_width();
	void draw(){

		print(get_absolute_x(),get_absolute_y());
		};
};

#endif
