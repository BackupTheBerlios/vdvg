#include "uv_window.h"


uv_window::uv_window(int breite=1024, int hoehe=768, uv_window *parent=0, int bit=32,
                          	int depth_size=24, int stencil_size=24,
                           	int doublebuffer=1, int noframe=0, char *label=0)
{
	static bool sdl_initialized=0;
	if(!sdl_initialized)	//SDL ist noch nicht initialisiert
	{
		init_SDL();			
		sdl_initialized=1;
		is_root_window=1;
		set_root_pointer(this);
	}
	else						//Ansonsten
	{
		is_root_window=0;
		parent->add_me(this);	//Window als neues Child window hinzufügen
	}
}

uv_window::~uv_window()
{
	
}

/*
Das Window kriegt ein neues Child Widget,
welches dann in einem dyn. array abgelegt wird.
*/
void uv_window::add_me(uv_widget *new_child)	
{
	
}

void uv_window::draw() //Zeichenfunktion
{
	if(is_root_window)
	{
		//Bildschirm löschen
	}
	else
	{
		//Fenster zeichnen
	}
	
	//Alle Child-draw funktionen aufrufen.
}

void uv_window::init_SDL(int breite=1280, int hoehe=1024, int bit=32, uv_window *parent=0,
                          	int depth_size=24, int stencil_size=24,
                           	int doublebuffer=1, int noframe=0, char *label=0)
{
	bool fullscreen=1;
	SDL_Surface *screen;
	int rgb_size[4];
	float gamma=0.0;
    Uint32 video_flags;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
   	{
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		exit( 1 );
   	}
	// Wenn keine Bit Angaben vorhanden sind, dann eine per default erstellen:
	if(bit == 0)
   	{
		if(SDL_GetVideoInfo()->vfmt->BitsPerPixel <= 8)
		{
	 		bit = 8;
      	}
      	else
      	{
	 		bit = 32;
      	}
   }
      // Flags des Video modes setzen
   //video_flags = SDL_OPENGLBLIT; //Für Blitten, performance--, daher inaktiv
   video_flags = SDL_OPENGL;
   //video_flags = SDL_RESIZABLE; //Wenn aktiv funktioniert nicht mehr alles

   //Auf Fullscreen prüfen
   if(fullscreen)
   {
      video_flags |= SDL_FULLSCREEN;
   }

   if (noframe)
   {
      video_flags |= SDL_NOFRAME;
   }

   // Farbtiefe initialisieren
   switch (bit)
   {
      case 8:
	 	rgb_size[0] = 3;
	 	rgb_size[1] = 3;
	 	rgb_size[2] = 2;
        rgb_size[3] = 0;
	 	break;
      //case 15:
      case 16:
	 	rgb_size[0] = 5;
	 	rgb_size[1] = 5;
	 	rgb_size[2] = 5;
        rgb_size[3] = 1;
	 	break;
      case 24:
        rgb_size[0] = 8;
        rgb_size[1] = 8;
        rgb_size[2] = 8;
        rgb_size[3] = 0;
      default:
	 	rgb_size[0] = 8;
	 	rgb_size[1] = 8;
	 	rgb_size[2] = 8;
        rgb_size[3] = 8;
        break;
   };
   //Farbtiefen an OpenGl übergeben
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     rgb_size[0]);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   rgb_size[1]);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    rgb_size[2]);
   SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   rgb_size[3]);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   depth_size);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doublebuffer);
   //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencil_size);

   /*if (false)//Keine ahnung was das soll
   { // Wenn false true wird, ist irgendwas nicht mehr gut
      SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
      SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
   }*/
   if ((screen = SDL_SetVideoMode(breite, hoehe, bit, video_flags))== NULL)
   {
      fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   // Titel des Fensters setzen:
   	if(label==0)
  	{
   		SDL_WM_SetCaption("Bennys SDL Fenster", "OpenGL");
	}
	else
	{
		SDL_WM_SetCaption(label,"");
	}
   // Gamma des Fensters setzen
   if(gamma != 0.0)
   {
      SDL_SetGamma(gamma, gamma, gamma);
   }
   //Initialisierung von OpenGl Abgeschlossen

   glViewport(0, 0, breite, hoehe);

   //Kameramatrix laden:
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0f, breite-1, hoehe-1, 0.0f, -100.0f, 100.0f);

   //Objekt und Modellmatrix laden:
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   //glClearColor(0.2f, 0.4f, 1.0f, 0.0f);
   glClearDepth(1.0f);
   //glClearStencil(24);
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_STENCIL_TEST);

   glDepthFunc(GL_LEQUAL);//GL_LESS);

   glShadeModel(GL_SMOOTH);

   glEnable(GL_TEXTURE_2D); // Aktiviert Textur Mapping
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Sehr gute Perspektive

   //Lösche den Bildschirm und den Depth Buffer:
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //Zeichnen fertig
   SDL_GL_SwapBuffers();

}
void uv_window::key_action(char key)
{
	
}

void uv_window::mouse_action(int x, int y,int what)
{
	
}
