#include "uv_window.h"


uv_window::uv_window (int breite, int hoehe, int win_x, int win_y,
                      uv_window * parent, int bit, int depth_size,
                      int stencil_size, int doublebuffer, int noframe,
                      char *label):uv_widget (win_x, win_y, breite, hoehe,
                                                      parent, label)
{
    static bool sdl_initialized = 0;
    // SDL ist noch nicht initialisiert
    if (!sdl_initialized)
    {
        init_SDL ();
        sdl_initialized = 1;
        is_root_window = 1;
        set_root_pointer (this);
    }
    else
    {
        is_root_window = 0;
        // Window als neues Child window hinzufügen
        parent->add_me (this);
    }
}

uv_window::~uv_window ()
{

}

/*
 * Das Window kriegt ein neues Child Widget.
 */
void uv_window::add_me (uv_widget * new_child)
{
    childs.push_back (new_child);
}

void uv_window::draw ()		// Zeichenfunktion
{
    if (is_root_window)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
        // Bildschirm löschen
    }
    else
    {
        glBegin (GL_QUADS);
        // Links Oben
        glColor3ub (255, 0, 0);
        glVertex2i (get_absolute_x(), get_absolute_y());
        // Rechts Oben
        glColor3ub (0, 255, 0);
        glVertex2i (get_absolute_x () + get_w (), get_absolute_y());
        // Rechts Unten
        glColor3ub (0, 0, 255);
        glVertex2i (get_absolute_x () + get_w (), get_absolute_y() + get_h ());
        // Links Unten
        glColor3ub (255, 255, 0);
        glVertex2i (get_absolute_x (), get_absolute_y() + get_h ());
        glEnd ();
    }

    // Alle Child-draw funktionen aufrufen.
    vector < uv_widget * >::iterator ite;
    for (ite = childs.begin (); ite != childs.end (); ++ite)
    {
        (*ite)->draw ();
    }
}

void uv_window::init_SDL (int breite, int hoehe, int bit,
                          uv_window * parent, int depth_size,
                          int stencil_size, int doublebuffer, int noframe,
                          char *label)
{
    bool fullscreen = 1;
    SDL_Surface *screen;
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
    // video_flags = SDL_RESIZABLE; //Wenn aktiv funktioniert nicht mehr
    // alles

    // Auf Fullscreen prüfen
    if (fullscreen)
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

    /*
     * if (false)//Keine ahnung was das soll { // Wenn false true wird,
     * ist irgendwas nicht mehr gut
     * SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
     * SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0); } 
     */
    if ((screen = SDL_SetVideoMode (breite, hoehe, bit, video_flags)) == NULL)
    {
        fprintf (stderr, "Couldn't set GL mode: %s\n", SDL_GetError ());
        SDL_Quit ();
        exit (1);
    }
    // Titel des Fensters setzen:
    if (label == 0)
    {
        SDL_WM_SetCaption ("Bennys SDL Fenster", "OpenGL");
    }
    else
    {
        SDL_WM_SetCaption (label, "");
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
    // ändern: Punkt(0,0) Oben Links punkt(640,480) unten rechts.

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
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Sehr gute
    // Perspektive

    // Lösche den Bildschirm und den Depth Buffer:
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Zeichnen fertig
    SDL_GL_SwapBuffers ();

}

void uv_window::key_action (int key,int mod, int what)
{

}

void uv_window::mouse_action (int x, int y, int what)
{

}
