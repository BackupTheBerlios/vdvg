//---------------------------------------------------------------------------
#ifndef _UV_TEXT_
#define _UV_TEXT_
//---------------------------------------------------------------------------
//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <string>

#include "uv_widget.h"
#include "uv_window.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
// Drawing routines are stolen from Nehe, Lesson 46 //43??
//---------------------------------------------------------------------------
class uv_text:public uv_widget
{
   private:
      struct font_data
      {
         float h;            // enthält die Höhe des Fonts.
	 GLuint * textures;  // enthält die Textur Id's
	 GLuint list_base;   // enthält die erste Display Listen Id

	 // Die Init Function wird ein Font mit
	 // der Höhe h aus der Datei fname erzeugen.
	 void init(const char * fname, unsigned int h);

	 // gebe alle Ressourcen, die mit dem Font verbunden sind, frei.
         void clean();
      };
      //font_data ft_font;
      GLuint * textures;	///< Holds the texture id's
      GLuint list_base;	        ///< Holds the first display list id
      float h;			///< Holds the height of the font.
      GLubyte red, green, blue; //Textfarbe

      void pop_projection_matrix();
      inline int next_p2 ( int a )	{int rval=1;while(rval<a) rval<<=1;	return rval;};
      void make_dlist ( FT_Face face, char ch, GLuint list_base, GLuint * tex_base );
      void pushScreenCoordinateMatrix();

   public:
      uv_text(int x, int y, int w, int h, uv_group *parent=0, char *mlabel=0, bool CFH=false);
      bool init(const char * fname, unsigned int h);
      void set_color(GLubyte red,GLubyte green,GLubyte blue);
      void clean();
      void print(float x, float y, const char *fmt, ...);
      void draw();
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
