#ifndef _UV_TEXT_
#define _UV_TEXT_


//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>


#include "SDL_opengl.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


// Drawing routines are stolen from Nehe, Lesson 46

class uv_text
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

public:
    uv_text(); //does currently nothing
    bool init(const char * fname, unsigned int h);
	void set_color(GLubyte red,GLubyte green,GLubyte blue);
	stringstream text;
    void clean();
    void print(float x, float y);
};

#endif
