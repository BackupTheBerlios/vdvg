#include "uv_text.h"
uv_text::uv_text():uv_widget(0,0,0,0,0,0)
{
   red=0xff;
   blue=0xff;
   green=0xff;
   len = 10001;
}

uv_text::uv_text(int mx,int my,int mh,int mw,uv_group *parent,char *label):uv_widget(mx,my,mh,mw, parent,label)
{
   parent->add_child(this);
   red=0xff;
   blue=0xff;
   green=0xff;
   len = 10001;
}


void uv_text::make_dlist ( FT_Face face, char ch, GLuint list_base, GLuint * tex_base )
{
    //The first thing we do is get FreeType to render our character
    //into a bitmap.  This actually requires a couple of FreeType commands:

    //Load the Glyph for our character.
    if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
        cout << "FT_Load_Glyph failed";

    //Move the face's glyph into a Glyph object.
    FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
        cout << "FT_Get_Glyph failed";

    //Convert the glyph to a bitmap.
    FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

    //This reference will make accessing the bitmap easier
    FT_Bitmap& bitmap=bitmap_glyph->bitmap;

    //Use our helper function to get the widths of
    //the bitmap data that we will need in order to create
    //our texture.
    int width = next_p2( bitmap.width );
    int height = next_p2( bitmap.rows );

    //Allocate memory for the texture data.
    GLubyte* expanded_data = new GLubyte[ 2 * width * height];

    //Here we fill in the data for the expanded bitmap.
    //Notice that we are using two channel bitmap (one for
    //luminocity and one for alpha), but we assign
    //both luminocity and alpha to the value that we
    //find in the FreeType bitmap.
    //We use the ?: operator so that value which we use
    //will be 0 if we are in the padding zone, and whatever
    //is the the Freetype bitmap otherwise.
    for(int j=0; j <height;j++) {
        for(int i=0; i < width; i++){
            expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] =
                                              (i>=bitmap.width || j>=bitmap.rows) ?
                                              0 : bitmap.buffer[i + bitmap.width*j];
        }
    }


    //Now we just setup some texture paramaters.
    glBindTexture( GL_TEXTURE_2D, tex_base[ch]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Here we actually create the texture itself, notice
    //that we are using GL_LUMINANCE_ALPHA to indicate that
    //we are using 2 channel data.
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                  0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );

    //With the texture created, we don't need to expanded data anymore
    delete [] expanded_data;

    //So now we can create the display list
    glNewList(list_base+ch,GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D,tex_base[ch]);
   
    //first we need to move over a little so that
    //the character has the right amount of space
    //between it and the one before it.
    glTranslatef(bitmap_glyph->left,0,0);

    //Now we move down a little in the case that the
    //bitmap extends past the bottom of the line
    //(this is only true for characters like 'g' or 'y'.
    glPushMatrix();
    glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

    //Now we need to account for the fact that many of
    //our textures are filled with empty padding space.
    //We figure what portion of the texture is used by
    //the actual character and store that information in
    //the x and y variables, then when we draw the
    //quad, we will only reference the parts of the texture
    //that we contain the character itself.
    float	x=(float)bitmap.width / (float)width,
            y=(float)bitmap.rows / (float)height;

    //Here we draw the texturemaped quads.
    //The bitmap that we got from FreeType was not
    //oriented quite like we would like it to be,
    //so we need to link the texture to the quad
    //so that the result will be properly aligned.
    glBegin(GL_QUADS);
    	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
    	glTexCoord2d(0,y); glVertex2f(0,0);
    	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
    	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
    glEnd();
    glPopMatrix();
    glTranslatef(face->glyph->advance.x >> 6 ,0,0);


    //increment the raster position as if we were a bitmap font.
    //(only needed if you want to calculate text length)
    glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

    //Finnish the display list
    glEndList();
}

bool uv_text::init(const char * fname, unsigned int h)
{
    //Allocate some memory to store the texture ids.
    textures = new GLuint[128];

    this->h=h;

    //Create and initilize a freetype font library.
    FT_Library library;
    if (FT_Init_FreeType( &library ))
    {
        cout << "FT_Init_FreeType failed";
        return 0;
    }

    //The object in which Freetype holds information on a given
    //font is called a "face".
    FT_Face face;

    //This is where we load in the font information from the file.
    //Of all the places where the code might die, this is the most likely,
    //as FT_New_Face will die if the font file does not exist or is somehow broken.
    if (FT_New_Face( library, fname, 0, &face ))
    {
        cout << "FT_New_Face failed (there is probably a problem with your font file)";
        return 0;
    }

    //For some twisted reason, Freetype measures font size
    //in terms of 1/64ths of pixels.  Thus, to make a font
    //h pixels high, we need to request a size of h*64.
    //(h << 6 is just a prettier way of writting h*64)
    FT_Set_Char_Size( face, h << 6, h << 6, 96, 96);

    //Here we ask opengl to allocate resources for
    //all the textures and displays lists which we
    //are about to create.
    list_base=glGenLists(128);
    glGenTextures( 128, textures );

    //This is where we actually create each of the fonts display lists.
    for(unsigned char i=0;i<128;i++)
        make_dlist(face,i,list_base,textures);

    //We don't need the face information now that the display
    //lists have been created, so we free the assosiated resources.
    FT_Done_Face(face);

    //Ditto for the library.
    FT_Done_FreeType(library);

    return 1;
}

void uv_text::clean()
{
    //
    glDeleteLists(list_base,128);
    glDeleteTextures(128,textures);
    delete [] textures;

}

void uv_text::pushScreenCoordinateMatrix()
{
    glPushAttrib(GL_TRANSFORM_BIT);
    GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	//void gluOrtho2D(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top)
	//gluOrtho2D(0,1024,768,0);
	gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
    glPopAttrib();


}


void uv_text::pop_projection_matrix()
{
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();


}

void uv_text::print( int x, int y)
{
    // We want a coordinate system where things coresponding to window pixels.
    pushScreenCoordinateMatrix();
	
	//Es ist einfacher, ein anderes Koordinatensystem zu wählen,
	//da sonst die Buchstaben nicht unten sondern oben bündig werden.
	//y muss ins Koordinantensystem umgerechnet werden:
	GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport); //Bildschirmgrösse abholen
	y = viewport[3]-y-(int)h; //Bildschirmhöhe - schrifthöhe - y
	//fertig
	
    GLuint font=list_base;
    float h=this->h/.63f;						//We make the height about 1.5* that of
	

    glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glListBase(font);

    float modelview_matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

    //This is where the text display actually happens.
    //For each line of text we reset the modelview matrix
    //so that the line's text will start in the correct position.
    //Notice that we need to reset the matrix, rather than just translating
    //down by h. This is because when each character is
    //draw it modifies the current matrix so that the next character
    //will be drawn immediatly after it.
	splitup();
	glColor3ub(red,green,blue); //passende Farbe laden
	
    for(unsigned int i=0;i<lines.size();i++) {


        glPushMatrix();
        glLoadIdentity();
        glTranslatef(x,y-h*i,0);
        glMultMatrixf(modelview_matrix);

        //  The commented out raster position stuff can be useful if you need to
        //  know the length of the text that you are creating.
        //  If you decide to use it make sure to also uncomment the glBitmap command
        //  in make_dlist().
        	glRasterPos2f(0,0);
        glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
        	int rpos[4];
        	glGetIntegerv(GL_CURRENT_RASTER_POSITION ,rpos);
		//cout << rpos[0] << endl;
        	len=x-rpos[0];

        glPopMatrix();

    }

    glPopAttrib();

    pop_projection_matrix();
	glBindTexture(GL_TEXTURE_2D, 0); //Texturen unbinden
	glColor3ub(0xff,0xff,0xff); //Farbe auf neutral zurücksetzen

}

void uv_text::set_color(GLubyte red,GLubyte green,GLubyte blue)
{
	this->red=red;
	this->blue=blue;
	this->green=green;
}

void uv_text::splitup()
{
	lines.clear();
	int pos=0;
	//int lastpos=0;
	while (text.str().find('\n',pos) != string::npos)
	{
		lines.push_back(text.str().substr(pos, text.str().find('\n',pos)-pos));
		pos = this->text.str().find('\n',pos)+1;
	}
	if (lines.empty()) lines.push_back(this->text.str());
}

int uv_text::get_width()
{
      if( len > 10000) print(0,0);
	return (int)len*-1+15; //+15, Korrektur für das Font System, das irgendwetwas falsch macht.
}

int uv_text::get_height()
{
	splitup();
	return lines.size()*((int)h);
}
