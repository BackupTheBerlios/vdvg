//---------------------------------------------------------------------------
// File:       main.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
void mainloop(uv_callback * cb);   //Hauptschleife
void menueinit();
void optionsinit();
void aboutinit();
void gameinit();
void menucallback();
void gamestartcallback();
void artificial_intelligence(uv_callback * cb);
void exitcallback();
//---------------------------------------------------------------------------
//Hauptprogramm
int main (int argc, char *argv[])
{
   uv_main::konfig.load_file("config.txt");
   uv_main::mainwindow = uv_main::konfig.get_mainwindow_attribute();
   uv_main::mainwindow.set_callback(mainloop);

   uv_main::img = uv_image::make_attribut(&uv_main::mainwindow, 0, 0, uv_main::konfig.get_config().width, uv_main::konfig.get_config().height, "Hintergrund", "background.jpg");

   uv_main::fps = uv_fpscounter::make_attribut(&uv_main::mainwindow, uv_main::mainwindow.get_w()-100, 0, 0, 0, uv_text::make_attribut(0, 0, 0, 0, 0, 16, "Frames", "Wait...", "Test.ttf", uv_color::make_color(255, 255, 255)),"FPS Counter");

   uv_main::menu = uv_container::make_attribut(&uv_main::mainwindow);
   uv_main::game = uv_container::make_attribut(&uv_main::mainwindow);
   uv_main::game.set_visible(0);
   uv_main::menu.set_visible(1);
   
   menueinit();
   gameinit();	

   uv_main::mainwindow.run();
   uv_main::konfig.save_file("config.txt");
   ki_thread::kill_thread();
   return 0;
};
//---------------------------------------------------------------------------
void mainloop(uv_callback * cb)
{
   //momentan noch leer
   if(ki_thread::check_end_of_calculations())
   {
      ki_thread::s_feld = ki_thread::hole_ergebnis();
      //Spielfeld zur�cksetzen
      for(int x=0; x<4; x++)
      {
         for(int y=0; y<4; y++)
         {
	    for (int z=0; z<4; z++)
	    {
	       for(int u=0; u<4; u++)
	       {
                  uv_main::gbuttons[x+y*4+z*16+u*64].set_status(ki_thread::s_feld.feld[x][y][z][u]);
               }
            }
         }
      }
      if(ki_thread::s_feld.gewonnen==1)
      {
         // Anzeigen, dass sp 1 gewonnen
      }
      if(ki_thread::s_feld.gewonnen==2)
      {
         // Anzeigen, dass comp gewonnen
      }
   }
};
//---------------------------------------------------------------------------

void menueinit()
{
  int width, height, buttonheight, buttonwidth;
  buttonwidth = 200;
  buttonheight = 50;
  width = uv_main::mainwindow.get_w();
  height = uv_main::mainwindow.get_h();

//(height-7*buttonheight)/2+x*buttonheight

  uv_main::mnewgame = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+0*buttonheight*2,buttonwidth,buttonheight,"newgame","Neues Spiel","");
  uv_main::moptions = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+1*buttonheight*2,buttonwidth,buttonheight,"newgame","Optionen","");
  uv_main::mabout = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+2*buttonheight*2,buttonwidth,buttonheight,"newgame","About","");
  uv_main::mexit  = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+3*buttonheight*2,buttonwidth,buttonheight,"newgame","Beenden","");

  uv_main::mnewgame.set_callback((voidcallback) gamestartcallback);
  uv_main::mexit.set_callback((voidcallback) exitcallback);
}

void gameinit()
{
 //agh abstandhalter grosshorizontal, ak abstandhalter klein, bu gamebuttonbreite
 //agv abstandhalter vertikal
   int width, height, ak, agh, agv, bu;
   width = uv_main::mainwindow.get_w();
   height = uv_main::mainwindow.get_h();

   agh=92;
   agv=75;
   ak=46;
   bu=30;

   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
	 for (int z=0; z<4; z++)
	 {
	    for(int w=0; w<4; w++)
	    {
               uv_gamebutton::position pos; pos.x_pos = x; pos.y_pos = y; pos.z_pos = z; pos.u_pos = w;
	       uv_main::gbuttons[x+y*4+z*16+w*64] = uv_gamebutton::make_attribut(&uv_main::game,agh+x*bu+w*(ak+4*bu), agv+y*bu+z*(ak+4*bu),bu,bu, pos,"","");
               uv_main::gbuttons[x+y*4+z*16+w*64].set_callback(artificial_intelligence);
	    }
	 }
      }
   }

   uv_main::gexit = uv_button::make_attribut(&uv_main::game,2*agh+3*ak+16*bu, agv,120,50,"a","Men�","");
   uv_main::gexit.set_callback((voidcallback) menucallback);
}

void gamestartcallback()
{
   uv_main::game.set_visible(1);
   uv_main::menu.set_visible(0);

   //Spielfeld zur�cksetzen
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
	 for (int z=0; z<4; z++)
	 {
	    for(int u=0; u<4; u++)
	    {
               uv_main::gbuttons[x+y*4+z*16+u*64].set_status(0);
            }
         }
      }
   }

   ki_thread::s_feld.reset();
}

void menucallback()
{
   uv_main::game.set_visible(0);
   uv_main::menu.set_visible(1);
}

void artificial_intelligence(uv_callback * cb)
{
   if(cb->ID != 18)
      return;
   uv_gamebutton::callback * gbcb;
   gbcb = static_cast<uv_gamebutton::callback*>(cb);
   if(ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] == 0 && !ki_thread::s_feld.gewonnen)
      uv_main::gbuttons[gbcb->pos.x_pos+gbcb->pos.y_pos*4+gbcb->pos.z_pos*16+gbcb->pos.u_pos*64].set_status(1);
   if(ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] == 0 && !ki_thread::s_feld.gewonnen)
      ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] = 1;

   ki_thread::start_calculations(ki_thread::s_feld);
}

void exitcallback()
{
   uv_main::mainwindow.set_run(false);
}


