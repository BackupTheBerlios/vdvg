//---------------------------------------------------------------------------
#include "uv_mainwindow.h"
//---------------------------------------------------------------------------
uv_mainwindow::uv_mainwindow(int mw, int mh,bool fullscreen, char *mlabel)
        :uv_group(0, 0, mw, mh, 0, mlabel)
{
    static bool already_exist = false;
    if(already_exist) return;
    already_exist = true;
    is_run = true;
    init_SDL(mw, mh, fullscreen, 32, 24, 24, 1, 0, mlabel);
};
//---------------------------------------------------------------------------
void uv_mainwindow::draw()
{
    //Überreste aus den Buffern löschen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Alle Childs zeichnen
    draw_childs();
};
//---------------------------------------------------------------------------
void uv_mainwindow::init_SDL (int breite, int hoehe, bool fullscreen, int bit,
                              int depth_size,
                              int stencil_size, int doublebuffer, int noframe,
                              char *label)
{
    //bool fullscreen = 0; //ändern
    //SDL_Surface *screen;
    int rgb_size[4];
    float gamma = 0.0;
    Uint32 video_flags;
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        exit (1);
    }
    // Wenn keine Bit Angaben vorhanden sind, dann eine per default
    // erstellen:
    if (bit == 0)
    {
        if (SDL_GetVideoInfo ()->vfmt->BitsPerPixel <= 8)
        {
            bit = 8;
        }
        else
        {
            bit = 32;
        }
    }
    // Flags des Video modes setzen
    // video_flags = SDL_OPENGLBLIT; //Für Blitten, performance--, daher
    // inaktiv
    video_flags = SDL_OPENGL;
    // video_flags = SDL_RESIZABLE;  //Wenn aktiv funktioniert nicht mehr
    // alles

    // Auf Fullscreen prüfen
    if(fullscreen)
    {
        video_flags |= SDL_FULLSCREEN;
    }

    if(noframe)
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
        // case 15:
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
    // Farbtiefen an OpenGl übergeben
    SDL_GL_SetAttribute (SDL_GL_RED_SIZE, rgb_size[0]);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, rgb_size[1]);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, rgb_size[2]);
    SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE, rgb_size[3]);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, depth_size);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, doublebuffer);
    // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencil_size);

    if((SDL_SetVideoMode(breite, hoehe, bit, video_flags)) == NULL)
    {
        fprintf (stderr, "Couldn't set GL mode: %s\n", SDL_GetError ());
        SDL_Quit ();
        exit (1);
    }
    // Titel des Fensters setzen:
    if (label == 0)
    {
        SDL_WM_SetCaption ("UV Gui", "UV Gui");
    }
    else
    {
        SDL_WM_SetCaption (label, "");//"uv.ico");
    }
    // Gamma des Fensters setzen
    if (gamma != 0.0)
    {
        SDL_SetGamma (gamma, gamma, gamma);
    }
    // Initialisierung von OpenGl Abgeschlossen

    glViewport (0, 0, breite, hoehe);

    // Kameramatrix laden:
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // glOrtho(0.0f, breite-1, hoehe-1, 0.0f, -100.0f, 100.0f);
    glOrtho (0, breite, hoehe, 0, -1.0, 1.0);	// Projektionsmatrix
    // Ã¤ndern: Punkt(0,0) Oben Links punkt(640,480) unten rechts.

    // Objekt und Modellmatrix laden:
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClearColor (0.2f, 0.4f, 1.0f, 0.0f);
    glClearDepth (1.0f);
    // glClearStencil(24);
    glEnable (GL_DEPTH_TEST);
    // glEnable(GL_STENCIL_TEST);

    glDepthFunc (GL_LEQUAL);	// GL_LESS);

    glShadeModel (GL_SMOOTH);

    glEnable (GL_TEXTURE_2D);	// Aktiviert Textur Mapping
    glEnable(GL_BLEND);	// Turn Blending On
    //  glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Sehr gute
    // Perspektive

    // Lösche den Bildschirm und den Depth Buffer:
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Zeichnen fertig
    SDL_GL_SwapBuffers ();
};
//---------------------------------------------------------------------------
void uv_mainwindow::run()
{
    SDL_Event event;
    bool last_was_mouse_down = false;
	bool last_was_key_down = false;
    while (SDL_PollEvent(&event) >= 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return;
        case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE) 
                return;
			if(last_was_key_down)
				break;
			key_action(event.key.keysym.sym, event.key.keysym.mod, event.key.type);
			last_was_key_down = true;
			break;
			
        case SDL_KEYUP:
			 if(!last_was_key_down)
                break;
            key_action(event.key.keysym.sym, event.key.keysym.mod, event.key.type);
			last_was_key_down = false;
            break;
			
        case SDL_MOUSEMOTION:
            set_mouse_x(event.motion.x);
            set_mouse_y(event.motion.y);

            //mouse_move_rel(event.motion.x,event.motion.y); //wird noch in rel. Bewegung umgerechnet
            mouse_move_rel(rel_mouse_x(event.motion.x), rel_mouse_y(event.motion.y));
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(last_was_mouse_down)
                break;
            last_was_mouse_down = true;
            mouse_action(event.button.x, event.button.y,
                         event.button.button, event.button.type);
            break;
        case SDL_MOUSEBUTTONUP:
            if(!last_was_mouse_down)
                break;
            last_was_mouse_down = false;
            mouse_action(event.button.x, event.button.y,
                         event.button.button, event.button.type);
            break;
        };
        draw();
        //Hauptschleifenfunktion aufrufen
        do_callback();
        SDL_GL_SwapBuffers();

        //Auf run prüfen
        if(!is_run)
            return;
    };
};
//---------------------------------------------------------------------------
void uv_mainwindow::key_action (int key,int mod, int what)
{
    key_action_childs(key, mod, what);
};
//---------------------------------------------------------------------------
bool uv_mainwindow::mouse_action (int x, int y, int button, int what)
{
    return mouse_action_childs(x, y, button, what);
};
//---------------------------------------------------------------------------
void uv_mainwindow::mouse_move_rel(int rel_x, int rel_y)
{
    mouse_move_rel_childs(rel_x, rel_y);
};
//---------------------------------------------------------------------------
void uv_mainwindow::set_run(bool Run)
{
    is_run = Run;
};
//---------------------------------------------------------------------------
bool uv_mainwindow::get_run()
{
    return is_run;
};
//---------------------------------------------------------------------------
