//---------------------------------------------------------------------------
#include "uv_image.h"
//---------------------------------------------------------------------------
uv_image::uv_image(string filename):uv_widget(0,0,0,0,0,0)
{
    uv_image();
    LoadImageFile(filename);
};
//---------------------------------------------------------------------------
uv_image::uv_image():uv_widget(0,0,0,0,0,0)
{
    loaded=false;
    w=0;
    h=0;
};
//---------------------------------------------------------------------------
uv_image::uv_image(int mx, int my, int mw, int mh, uv_group *parent, char *mlabel):uv_widget(mx,my,mw,mh,parent,0)
{
    parent->add_child(this);
	loaded=false;
    w=0;
    h=0;
	LoadImageFile(mlabel);
};
//---------------------------------------------------------------------------
bool uv_image::LoadImageFile(string fname)
{
 	static map<string,uv_image*> texturindex;
	map<string,uv_image*>::iterator ite;
	ite = texturindex.find(fname); 
	if ( ite != texturindex.end()) //Dieses font_set wird bereits verwendet...
	{ 
		//sozusagen this=ite->second....
		w = ite->second->get_texture_w(); //Laden
		h = ite->second->get_texture_w(); //Laden
		textur = ite->second->get_texture_index();
		return 1;
	}
	
	GLuint global_texture = 0;
    SDL_Surface *image;
    GLfloat texcoord[4];

    // Load the image (could use SDL_image library here)
    image = IMG_Load(fname.c_str());
    if(image == NULL)
    {
        cout << "Error: Can't open " << fname <<endl;
        return false;
    }
    w = image->w;
    h = image->h;

    // Convert the image into an OpenGL texture
    global_texture = SDL_GL_LoadTexture(image, texcoord);

    // We don't need the original image anymore
    SDL_FreeSurface(image);
    if( !global_texture)
    {
        cout << "Error: Can't convert "<< fname <<endl;
        return false;
    }
    textur = global_texture;
    cout << global_texture;

    texMinX = texcoord[0];
    texMinY = texcoord[1];
    texMaxX = texcoord[2];
    texMaxY = texcoord[3];
	
	texturindex.insert(pair<string,uv_image*>(fname,this));
    return true;
};
//---------------------------------------------------------------------------
GLuint uv_image::SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
    GLuint texture;
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    // Use the surface width and height expanded to powers of 2
    w = power_of_two(surface->w);
    h = power_of_two(surface->h);
    texcoord[0] = 0.0f;			   // Min X
    texcoord[1] = 0.0f;			   // Min Y
    texcoord[2] = (GLfloat)surface->w / w;  // Max X
    texcoord[3] = (GLfloat)surface->h / h;  // Max Y

    image = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                 w, h,
                                 32,
                                 // OpenGL RGBA masks
                                #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                                 0x000000FF,
                                 0x0000FF00,
                                 0x00FF0000,
                                 0xFF000000
                                #else
                                 0xFF000000,
                                 0x00FF0000,
                                 0x0000FF00,
                                 0x000000FF
                                #endif
                                );
    if(image == NULL)
    {
        cout << "Error occured while creating SDL Surface for Image loading."<<endl;
        return false;
    }

    // Save the alpha blending attributes
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    {
        SDL_SetAlpha(surface, 0, 0);
    }

    // Copy the surface into the GL texture image
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, image, &area);

    // Restore the alpha blending attributes
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }

    // Create an OpenGL texture for the image
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 w, h,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image->pixels);
    SDL_FreeSurface(image); // No longer needed
    return texture;
};
//---------------------------------------------------------------------------
int uv_image::power_of_two(int input)
{
    int value = 1;
    while(value < input)
    {
        value <<= 1;
    }
    return value;
};
//---------------------------------------------------------------------------
void uv_image::draw_size(int x, int y, int w, int h,
                         GLfloat picx, GLfloat picy, GLfloat picw, GLfloat pich)
{
    // x,y,w,h sind OK
    glBindTexture(GL_TEXTURE_2D, textur);
    glBegin(GL_TRIANGLE_STRIP);
    if(picx!=-1)
    {
       //Links Oben
       glTexCoord2f(picx, picy); glVertex2i( x, y);
       //Rechts Oben
       glTexCoord2f(picw, picy); glVertex2i( x+w, y);
       //Links Unten
       glTexCoord2f(picx, pich); glVertex2i( x, y+h);
       //Rechts Unten
       glTexCoord2f(picw, pich); glVertex2i( x+w, y+h);
    }
    else
    {
       //Links Oben
       glTexCoord2f(texMinX, texMinY); glVertex2i( x, y);
       //Rechts Oben
       glTexCoord2f(texMaxX, texMinY); glVertex2i( x+w, y);
       //Links Unten
       glTexCoord2f(texMinX, texMaxY); glVertex2i( x, y+h);
       //Rechts Unten
       glTexCoord2f(texMaxX, texMaxY); glVertex2i( x+w, y+h);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); //Textur unbinden, für andere Zeichnungsop.
};
//---------------------------------------------------------------------------
