//---------------------------------------------------------------------------
// File:       main.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
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
void ok1callback(uv_callback * cb);
void ok2callback(uv_callback * cb);
void exitcallback();
void ocancelcb();
void ookcb();
void oresolutioncallback(uv_callback *cb);
void optionscb();
void gookcb(uv_callback * cb);
void goleichtercb(uv_callback * cb);
void goschwerercb(uv_callback * cb);
void goselect1cb(uv_callback * cb);
void goselect2cb(uv_callback * cb);
void goselect3cb(uv_callback * cb);
void goselect4cb(uv_callback * cb);
void aboutcallback();
void aboutclosecb();
//---------------------------------------------------------------------------
//Hauptprogramm
int main (int argc, char *argv[])
{
   uv_main::konfig.load_file("config.txt");
   uv_main::mainwindow = uv_main::konfig.get_mainwindow_attribute();
   uv_main::mainwindow.set_callback(mainloop);

   uv_main::fps = uv_fpscounter::make_attribut(&uv_main::mainwindow, uv_main::mainwindow.get_w()-100, 0, 0, 0, uv_text::make_attribut(0, 0, 0, 0, 0, 16, "Frames", "Wait...", "Test.ttf", uv_color::make_color(255, 255, 255)),"FPS Counter");

   uv_main::menu = uv_container::make_attribut(&uv_main::mainwindow);
   uv_main::game = uv_container::make_attribut(&uv_main::mainwindow);
   uv_main::game.set_visible(0);
   uv_main::menu.set_visible(1);

   aboutinit();
   menueinit();
   gameinit();
   optionsinit();
//	uv_main::options.set_visible(1);
//	uv_main::mainwindow.set_on_top_widget(&uv_main::options);
//TEST
/*	uv_dropdown drop;
	vector<string> lolo;
	lolo.push_back("hellou");
	lolo.push_back("hellaau");
	lolo.push_back("hilleu");
	lolo.push_back("hollau");
	drop = uv_dropdown::make_attribut(&uv_main::menu,&uv_main::mainwindow,60,60,200,40,"", lolo, "");*/
///TEST
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
      //Bei "Computer gegen Computer" prüfen, ob gekehrt werden muss
      if(!uv_main::compcomp && uv_main::spielmodus == 3)
      {
         for(int x=0; x<4; x++)
         {
            for(int y=0; y<4; y++)
            {
	       for (int z=0; z<4; z++)
	       {
	          for(int u=0; u<4; u++)
	          {
                     ki_thread::s_feld.feld[x][y][z][u] = (ki_thread::s_feld.feld[x][y][z][u] == 1) ? 2 : ((ki_thread::s_feld.feld[x][y][z][u] == 2) ? 1 : 0);
                  }
               }
            }
         }
         uv_main::compcomp = false;
      }
      //Spielfeld zurücksetzen
      for(int x=0; x<4; x++)
      {
         for(int y=0; y<4; y++)
         {
	    for (int z=0; z<4; z++)
	    {
	       for(int u=0; u<4; u++)
	       {
                  if(uv_main::gbuttons[x+y*4+z*16+u*64].get_status() != ((ki_thread::s_feld.feld[x][y][z][u] == 0) ? 0 : ((uv_main::spielmodus == 0 || uv_main::spielmodus == 2) ? ki_thread::s_feld.feld[x][y][z][u] : ((ki_thread::s_feld.feld[x][y][z][u] == 1) ? 2 : 1))))
                     uv_main::gbuttons[x+y*4+z*16+u*64].set_blink((uv_main::spielmodus != 3) ? 5.0 : 1.0);
                  uv_main::gbuttons[x+y*4+z*16+u*64].set_status((ki_thread::s_feld.feld[x][y][z][u] == 0) ? 0 : ((uv_main::spielmodus == 0 || uv_main::spielmodus == 2) ? ki_thread::s_feld.feld[x][y][z][u] : ((ki_thread::s_feld.feld[x][y][z][u] == 1) ? 2 : 1)));
               }
            }
         }
      }
      if(ki_thread::s_feld.gewonnen==1)
      {
         // Anzeigen, dass sp 1 gewonnen
         uv_main::won.set_visible(true, true);
	 //on top setzen
	 uv_main::mainwindow.set_on_top_widget(&uv_main::won);
         if(uv_main::spielmodus == 0 || uv_main::spielmodus == 1)
         {
            uv_main::verloren.pushtext("Sie haben leider verloren. :-(");
            uv_main::gewonnen1.pushtext("Gratulation!");
            uv_main::gewonnen2.pushtext("Sie haben den Computer geschlagen.");
         }
         else
         {
            uv_main::verloren.pushtext("Spieler 2 hat gewonnen!");
            uv_main::gewonnen1.pushtext("");
            uv_main::gewonnen2.pushtext("Spieler 1 hat gewonnen!");
         }
      }
      if(ki_thread::s_feld.gewonnen==2)
      {
         // Anzeigen, dass comp gewonnen
         uv_main::lost.set_visible(true, true);
	 //on top setzen
	 uv_main::mainwindow.set_on_top_widget(&uv_main::lost);
         if(uv_main::spielmodus == 0 || uv_main::spielmodus == 1)
         {
            uv_main::verloren.pushtext("Sie haben leider verloren. :-(");
            uv_main::gewonnen1.pushtext("Gratulation!");
            uv_main::gewonnen2.pushtext("Sie haben den Computer geschlagen.");
         }
         else
         {
            uv_main::verloren.pushtext("Spieler 2 hat gewonnen!");
            uv_main::gewonnen1.pushtext("");
            uv_main::gewonnen2.pushtext("Spieler 1 hat gewonnen!");
         }
      }
      if(ki_thread::s_feld.gewonnen==0 && uv_main::spielmodus == 3 && uv_main::game.get_visible() && !uv_main::gameoptionen.get_visible())
      {
         if(uv_main::compcomp)
         {
            for(int x=0; x<4; x++)
            {
               for(int y=0; y<4; y++)
               {
	          for (int z=0; z<4; z++)
	          {
	             for(int u=0; u<4; u++)
	             {
                        ki_thread::s_feld.feld[x][y][z][u] = (ki_thread::s_feld.feld[x][y][z][u] == 1) ? 2 : ((ki_thread::s_feld.feld[x][y][z][u] == 2) ? 1 : 0);
                     }
                  }
               }
            }
            uv_main::compcomp = false;
         }
         else
         {
            uv_main::compcomp = true;
         }
         ki_thread::start_calculations(ki_thread::s_feld);
      }
      if(!uv_main::game.get_visible() || uv_main::gameoptionen.get_visible())
      {
         //Spielfeld zurücksetzen
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

  uv_main::img1 = uv_image::make_attribut(&uv_main::menu, 0, 0, uv_main::konfig.get_config().width, uv_main::konfig.get_config().height, "Hintergrund", ((uv_main::konfig.get_config().width == 1600 && uv_main::konfig.get_config().height == 1200) || (uv_main::konfig.get_config().width == 800 && uv_main::konfig.get_config().height == 600)) ? "menubackground high.tga" : ((uv_main::konfig.get_config().width == 1280 && uv_main::konfig.get_config().height == 1024) ? "menubackground medium.tga" : "menubackground low.tga"));
  uv_main::mnewgame = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+0*buttonheight*2,buttonwidth,buttonheight,"newgame","Neues Spiel","");
  uv_main::moptions = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+1*buttonheight*2,buttonwidth,buttonheight,"newgame","Optionen","");
  uv_main::mabout = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+2*buttonheight*2,buttonwidth,buttonheight,"newgame","About","");
  uv_main::mexit  = uv_button::make_attribut(&uv_main::menu, (width-buttonwidth)/2,(height-7*buttonheight)/2+3*buttonheight*2,buttonwidth,buttonheight,"newgame","Beenden","");

  uv_main::mabout.set_callback((voidcallback) aboutcallback);
  uv_main::mnewgame.set_callback((voidcallback) gamestartcallback);
  uv_main::mexit.set_callback((voidcallback) exitcallback);
}
//---------------------------------------------------------------------------
void gameinit()
{
 //agh abstandhalter grosshorizontal, ak abstandhalter klein, bu gamebuttonbreite
 //agv abstandhalter vertikal
   int width, height, ak, agh, agv, bu;
   width = uv_main::mainwindow.get_w();
   height = uv_main::mainwindow.get_h();

   uv_main::img2 = uv_image::make_attribut(&uv_main::game, 0, 0, uv_main::konfig.get_config().width, uv_main::konfig.get_config().height, "Hintergrund", ((uv_main::konfig.get_config().width == 1600 && uv_main::konfig.get_config().height == 1200) || (uv_main::konfig.get_config().width == 800 && uv_main::konfig.get_config().height == 600)) ? "gamebackground high.tga" : ((uv_main::konfig.get_config().width == 1280 && uv_main::konfig.get_config().height == 1024) ? "gamebackground medium.tga" : "gamebackground low.tga"));

   agh=92;
   agv=75;
   ak=46;
   bu=(height-2*agv-3*ak)/16;

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

   uv_main::gexit = uv_button::make_attribut(&uv_main::game, 2*agh+3*ak+16*bu, agv+60, 200, 50, "a", "Menue","");//2*agh+3*ak+16*bu, agv,120,50,"a","Menü","");
   uv_main::gexit.set_callback((voidcallback) menucallback);
   uv_main::new_game = uv_button::make_attribut(&uv_main::game, 2*agh+3*ak+16*bu, agv, 200, 50, "a", "Neues Spiel","");
   uv_main::new_game.set_callback((voidcallback) gamestartcallback);
   uv_main::exit = uv_button::make_attribut(&uv_main::game, 2*agh+3*ak+16*bu, agv+120, 200, 50, "a", "Beenden","");
   uv_main::exit.set_callback((voidcallback) exitcallback);

   uv_main::lost = uv_window::make_attribut(&uv_main::mainwindow, (width-500)/2, (height-200)/2, 500, 150, "Lost_window", "Verloren!", "", "windowdesign.tga", false, false, true, false);
   uv_main::won  = uv_window::make_attribut(&uv_main::mainwindow, (width-500)/2, (height-200)/2, 500, 170, "Won_window",  "Gewonnen!", "", "windowdesign.tga", false, false, true, false);
   uv_main::ok1  = uv_button::make_attribut(&uv_main::lost, 175, 90, 150, 40, "b", "OK","");
   uv_main::ok2  = uv_button::make_attribut(&uv_main::won , 175, 110, 150, 40, "c", "OK","");
   uv_main::verloren = uv_text::make_attribut(&uv_main::lost, 20, 70, 260, 50, 20, "Verloren Text", "Sie haben leider verloren. :-(", "Test.ttf",uv_color::make_color(255,255,255));
   uv_main::gewonnen1 = uv_text::make_attribut(&uv_main::won , 20, 50, 260, 50, 20, "Verloren Text", "Gratulation!", "Test.ttf",uv_color::make_color(255,255,255));
   uv_main::gewonnen2 = uv_text::make_attribut(&uv_main::won , 20, 90, 260, 50, 20, "Verloren Text", "Sie haben den Computer geschlagen.", "Test.ttf",uv_color::make_color(255,255,255));
   uv_main::ok1.set_callback(ok1callback);
   uv_main::ok2.set_callback(ok2callback);
   uv_main::lost.set_visible(false);
   uv_main::won.set_visible(false);

   //Gameoptioneninit
   uv_main::gameoptionen = uv_window::make_attribut(&uv_main::mainwindow, (width-500)/2, (height-320)/2, 500, 320, "Gameoptionen", "Gameoptionen", "", "windowdesign.tga", false, false, true, false);
   uv_main::gook = uv_button::make_attribut(&uv_main::gameoptionen, 175, 260, 150, 40, "ok", "OK", "");
   uv_main::gook.set_callback(gookcb);
   uv_main::goschwierigkeit = uv_text::make_attribut(&uv_main::gameoptionen, 20, 210, 380, 40, 20, "Schwierigkeit", "Schwierigkeitsgrad: ", "Test.ttf", uv_color::make_color(255, 255, 255));
   uv_main::goschwierigkeitsgrad = uv_text::make_attribut(&uv_main::gameoptionen, 70, 240, 10, 40, 20, "Schwierigkeitsgrad", "5", "Test.ttf", uv_color::make_color(255, 255, 255));
   uv_main::goschwierigkeitsstufe = uv_text::make_attribut(&uv_main::gameoptionen, 150, 240, 200, 40, 20, "Schwierigkeitsstufe", "mittel", "Test.ttf", uv_color::make_color(255, 255, 255));
   uv_main::goleichter = uv_button::make_attribut(&uv_main::gameoptionen,  20, 220, 30, 30, "leichter", "<", "");
   uv_main::goleichter.set_callback(goleichtercb);
   uv_main::goschwerer = uv_button::make_attribut(&uv_main::gameoptionen, 100, 220, 30, 30, "schwerer", ">", "");
   uv_main::goschwerer.set_callback(goschwerercb);
   uv_main::gospielmodus   = uv_text::make_attribut(&uv_main::gameoptionen, 20, 50, 380, 40, 20, "Spielmodi", "Spielmodus: ", "Test.ttf", uv_color::make_color(255, 255, 255));
   uv_main::gomenschcomp   = uv_checkbox::make_attribut(&uv_main::gameoptionen, 20, 70,  310, 16, uv_image::make_attribut(0,0,0,16,16,"Checkbox","unselected.tga"),uv_image::make_attribut(0,0,0,16,16,"Checkbox","selected.tga"),uv_text::make_attribut(0,20,20,0,0,20,"Buttontext","Mensch gegen Computer", "Test.ttf", uv_color::make_color(255, 255, 255)), "spielmodus");
   uv_main::gocompmensch   = uv_checkbox::make_attribut(&uv_main::gameoptionen, 20, 100, 310, 16, uv_image::make_attribut(0,0,0,16,16,"Checkbox","unselected.tga"),uv_image::make_attribut(0,0,0,16,16,"Checkbox","selected.tga"),uv_text::make_attribut(0,20,20,0,0,20,"Buttontext","Computer gegen Mensch", "Test.ttf", uv_color::make_color(255, 255, 255)), "spielmodus");
   uv_main::gomenschmensch = uv_checkbox::make_attribut(&uv_main::gameoptionen, 20, 130, 310, 16, uv_image::make_attribut(0,0,0,16,16,"Checkbox","unselected.tga"),uv_image::make_attribut(0,0,0,16,16,"Checkbox","selected.tga"),uv_text::make_attribut(0,20,20,0,0,20,"Buttontext","Mensch gegen Mensch", "Test.ttf", uv_color::make_color(255, 255, 255)), "spielmodus");
   uv_main::gocompcomp     = uv_checkbox::make_attribut(&uv_main::gameoptionen, 20, 160, 310, 16, uv_image::make_attribut(0,0,0,16,16,"Checkbox","unselected.tga"),uv_image::make_attribut(0,0,0,16,16,"Checkbox","selected.tga"),uv_text::make_attribut(0,20,20,0,0,20,"Buttontext","Computer gegen Computer", "Test.ttf", uv_color::make_color(255, 255, 255)), "spielmodus");
   uv_main::gomenschcomp.set_callback(goselect1cb);
   uv_main::gocompmensch.set_callback(goselect2cb);
   uv_main::gomenschmensch.set_callback(goselect3cb);
   uv_main::gocompcomp.set_callback(goselect4cb);
   uv_main::gomenschcomp.set_checked(true);
   uv_main::gameoptionen.set_visible(false);

   uv_main::compcomp = true;
   uv_main::spielmodus = 0;
}
//---------------------------------------------------------------------------
void gamestartcallback()
{
   uv_main::game.set_visible(1);
   uv_main::menu.set_visible(0);
   uv_main::gameoptionen.set_visible(true, true);
   //on top setzen
   uv_main::mainwindow.set_on_top_widget(&uv_main::gameoptionen);
   uv_main::goschwierigkeitsgrad.pushtext("5");
   uv_main::goschwierigkeitsstufe.pushtext("mittel");

   //Spielfeld zurücksetzen
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
//---------------------------------------------------------------------------
void menucallback()
{
   uv_main::game.set_visible(0);
   uv_main::menu.set_visible(1);
}
//---------------------------------------------------------------------------
void artificial_intelligence(uv_callback * cb)
{
   if(cb->ID != 18)
      return;
   uv_gamebutton::callback * gbcb;
   gbcb = static_cast<uv_gamebutton::callback*>(cb);
   //Wenn "Mensch gegen Computer" oder "Computer gegen Mensch"
   if(uv_main::spielmodus == 0 || uv_main::spielmodus == 1)
   {
      if(ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] == 0 && !ki_thread::s_feld.gewonnen)
      {
         uv_main::gbuttons[gbcb->pos.x_pos+gbcb->pos.y_pos*4+gbcb->pos.z_pos*16+gbcb->pos.u_pos*64].set_blink(2.0);
         uv_main::gbuttons[gbcb->pos.x_pos+gbcb->pos.y_pos*4+gbcb->pos.z_pos*16+gbcb->pos.u_pos*64].set_status((uv_main::spielmodus == 0) ? 1 : 2);
      }
      if(ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] == 0 && !ki_thread::s_feld.gewonnen)
      {
         ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] = 1;
         ki_thread::start_calculations(ki_thread::s_feld);
      }
   }
   if(uv_main::spielmodus == 2)
   {
      if(ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] == 0 && !ki_thread::s_feld.gewonnen)
      {
         uv_main::compcomp = !uv_main::compcomp;
         uv_main::gbuttons[gbcb->pos.x_pos+gbcb->pos.y_pos*4+gbcb->pos.z_pos*16+gbcb->pos.u_pos*64].set_blink(2.0);
         uv_main::gbuttons[gbcb->pos.x_pos+gbcb->pos.y_pos*4+gbcb->pos.z_pos*16+gbcb->pos.u_pos*64].set_status((uv_main::compcomp) ? 1 : 2);
         ki_thread::s_feld.feld[gbcb->pos.x_pos][gbcb->pos.y_pos][gbcb->pos.z_pos][gbcb->pos.u_pos] = (uv_main::compcomp) ? 1 : 2;
         ki_thread::start_calculations(ki_thread::s_feld);
      }
   }
}
//---------------------------------------------------------------------------
void ok1callback(uv_callback * cb)
{
   uv_main::lost.set_visible(false);
   //ON TOP entfernen
   uv_main::mainwindow.set_on_top_widget(0);
}
//---------------------------------------------------------------------------
void ok2callback(uv_callback * cb)
{
   uv_main::won.set_visible(false);
   uv_main::mainwindow.set_on_top_widget(0);
}
//---------------------------------------------------------------------------
void exitcallback()
{
   uv_main::mainwindow.set_run(false);
}
//---------------------------------------------------------------------------
void optionsinit()
{
   uv_color text_color = {0xff, 0xff, 0xff};
   uv_main::options=uv_window::make_attribut(&uv_main::mainwindow,20,20,300,300,"","","","",0,0,1,0);
   uv_main::ofullscreen=uv_checkbox::make_attribut(&uv_main::options,30,40,115,16,uv_image::make_attribut(0,0,0,16,16,"Checkbox","unchecked.tga"),uv_image::make_attribut(0,0,0,16,16,"Checkbox","checked.tga"),uv_text::make_attribut(0,20,16,0,0,16,"Buttontext","Fullscreen","Test.ttf",text_color),"fullscreen");
   uv_main::ook=uv_button::make_attribut(&uv_main::options,10,250,105,40,"a","OK","");
   uv_main::ocancel=uv_button::make_attribut(&uv_main::options,125,250,165,40,"a","Abbrechen","");

   uv_main::ocancel.set_callback((voidcallback) ocancelcb);
   uv_main::ook.set_callback((voidcallback) ookcb);
   uv_main::options.set_visible(0);
   uv_main::moptions.set_callback((voidcallback) optionscb);
   uv_main::ofullscreen.set_checked(uv_main::konfig.get_config().fullscreen);

	uv_main::orestext = uv_text::make_attribut(&uv_main::options,30,110,200,16,16,"","Aufloesung:","Test.ttf",uv_color::make_color(255,255,255));
	uv_main::oinfotext = uv_text::make_attribut(&uv_main::options,30,176,200,16,16,"","Aenderungen erfordern","Test.ttf",uv_color::make_color(255,255,255));

	uv_main::oinfotextb = uv_text::make_attribut(&uv_main::options,30,200,200,16,16,"","Neustart","Test.ttf",uv_color::make_color(255,255,255));
	uv_main::vec_resolutions.push_back("800x600");
	uv_main::vec_resolutions.push_back("1024x768");
	uv_main::vec_resolutions.push_back("1280x1024");
	uv_main::vec_resolutions.push_back("1600x1200");
	uv_main::oresolution = uv_dropdown::make_attribut(&uv_main::options,&uv_main::mainwindow,30,120,200,30,"", uv_main::vec_resolutions, "");
	uv_main::oresolution.set_act_ele((uv_main::konfig.get_config().width/200)-4);
}
//---------------------------------------------------------------------------
void ocancelcb()
{
   uv_main::options.set_visible(0);
   //ON TOP entfernen
   uv_main::mainwindow.set_on_top_widget(0);
}
//---------------------------------------------------------------------------
void ookcb()
{
   bool temp = uv_main::konfig.get_config().fullscreen;
   SDL_Surface *sf = SDL_GetVideoSurface();

   uv_main::options.set_visible(0);
   //ON TOP entfernen
   uv_main::mainwindow.set_on_top_widget(0);
   uv_main::konfig.set_fullscreen(uv_main::ofullscreen.get_checked());
   if(temp != uv_main::ofullscreen.get_checked()) SDL_WM_ToggleFullScreen(sf);
	config tmp = uv_main::konfig.get_config();
	switch( uv_main::oresolution.get_act_ele() )
		{
			case 0:
				tmp.width = 800;
				tmp.height = 600;
				break;
			case 1:
				tmp.width = 1024;
				tmp.height = 768;
				break;
			case 2:
				tmp.width = 1280;
				tmp.height = 1024;
				break;
			case 4:
				tmp.width = 1600;
				tmp.height = 1200;
				break;
		}
	uv_main::konfig.set_config(tmp);
}
//---------------------------------------------------------------------------
void optionscb()
{
   uv_main::options.set_visible(true, true);
   uv_main::mainwindow.set_on_top_widget(&uv_main::options);
}
//---------------------------------------------------------------------------
void gookcb(uv_callback * cb)
{
   uv_main::gameoptionen.set_visible(false);
   //On Top entfernen
   uv_main::mainwindow.set_on_top_widget(0);

   uv_main::spielmodus = (uv_main::gomenschcomp.get_checked()) ? 0 : ((uv_main::gocompmensch.get_checked()) ? 1 : ((uv_main::gomenschmensch.get_checked()) ? 2 : 3));

   if(uv_main::spielmodus == 1 || uv_main::spielmodus == 3)
      ki_thread::start_calculations(ki_thread::s_feld);

   if(uv_main::spielmodus == 2)
      ki_thread::s_feld.schwierigkeitsgrad = 10;

   uv_main::compcomp = (uv_main::spielmodus == 2) ? false : true;
}
//---------------------------------------------------------------------------
void goleichtercb(uv_callback * cb)
{
   if(ki_thread::s_feld.schwierigkeitsgrad > 0)
      ki_thread::s_feld.schwierigkeitsgrad--;
   uv_main::goschwierigkeitsgrad.pushtext(uv_main::IntToString(ki_thread::s_feld.schwierigkeitsgrad));
   switch(ki_thread::s_feld.schwierigkeitsgrad)
   {
      case 0:
         uv_main::goschwierigkeitsstufe.pushtext("extrem leicht");
         break;
      case 1:
         uv_main::goschwierigkeitsstufe.pushtext("sehr leicht");
         break;
      case 2:
         uv_main::goschwierigkeitsstufe.pushtext("leicht");
         break;
      case 3:
         uv_main::goschwierigkeitsstufe.pushtext("recht leicht");
         break;
      case 4:
      case 5:
      case 6:
         uv_main::goschwierigkeitsstufe.pushtext("mittel");
         break;
      case 7:
         uv_main::goschwierigkeitsstufe.pushtext("schwer");
         break;
      case 8:
         uv_main::goschwierigkeitsstufe.pushtext("sehr schwer");
         break;
      case 9:
         uv_main::goschwierigkeitsstufe.pushtext("extrem schwer");
         break;
   }
}
//---------------------------------------------------------------------------
void goschwerercb(uv_callback * cb)
{
   if(ki_thread::s_feld.schwierigkeitsgrad < 9)
      ki_thread::s_feld.schwierigkeitsgrad++;
   uv_main::goschwierigkeitsgrad.pushtext(uv_main::IntToString(ki_thread::s_feld.schwierigkeitsgrad));
   switch(ki_thread::s_feld.schwierigkeitsgrad)
   {
      case 0:
         uv_main::goschwierigkeitsstufe.pushtext("extrem leicht");
         break;
      case 1:
         uv_main::goschwierigkeitsstufe.pushtext("sehr leicht");
         break;
      case 2:
         uv_main::goschwierigkeitsstufe.pushtext("leicht");
         break;
      case 3:
         uv_main::goschwierigkeitsstufe.pushtext("recht leicht");
         break;
      case 4:
      case 5:
      case 6:
         uv_main::goschwierigkeitsstufe.pushtext("mittel");
         break;
      case 7:
         uv_main::goschwierigkeitsstufe.pushtext("schwer");
         break;
      case 8:
         uv_main::goschwierigkeitsstufe.pushtext("sehr schwer");
         break;
      case 9:
         uv_main::goschwierigkeitsstufe.pushtext("extrem schwer");
         break;
   }
}
//---------------------------------------------------------------------------
void goselect1cb(uv_callback * cb)
{
   uv_main::gomenschcomp.set_checked(true);
   uv_main::gocompmensch.set_checked(false);
   uv_main::gomenschmensch.set_checked(false);
   uv_main::gocompcomp.set_checked(false);
}
//---------------------------------------------------------------------------
void goselect2cb(uv_callback * cb)
{
   uv_main::gomenschcomp.set_checked(false);
   uv_main::gocompmensch.set_checked(true);
   uv_main::gomenschmensch.set_checked(false);
   uv_main::gocompcomp.set_checked(false);
}
//---------------------------------------------------------------------------
void goselect3cb(uv_callback * cb)
{
   uv_main::gomenschcomp.set_checked(false);
   uv_main::gocompmensch.set_checked(false);
   uv_main::gomenschmensch.set_checked(true);
   uv_main::gocompcomp.set_checked(false);
}
//---------------------------------------------------------------------------
void goselect4cb(uv_callback * cb)
{
   uv_main::gomenschcomp.set_checked(false);
   uv_main::gocompmensch.set_checked(false);
   uv_main::gomenschmensch.set_checked(false);
   uv_main::gocompcomp.set_checked(true);
}

void oresolutioncallback(uv_callback * cb)
{
	if(cb->ID == 22)
	{
//		config tmp = uv_main::konfig.get_config();
		uv_dropdown::callback * drcb;
   	drcb = static_cast<uv_dropdown::callback*>(cb);
		uv_main::oresnumtemp = drcb->num;
/*		switch( drcb->num )
		{
			case 0:
				tmp.width = 800;
				tmp.height = 600;
				break;
			case 1:
				tmp.width = 1024;
				tmp.height = 768;
				break;
			case 2:
				tmp.width = 1280;
				tmp.height = 1024;
				break;
			case 4:
				tmp.width = 1600;
				tmp.height = 1200;
				break;
		}*/
//		uv_main::konfig.set_config(tmp);
	}
}

//---------------------------------------------------------------------------
//Eine Hilfsfunktion, um ints in strings zu konvertieren
std::string uv_main::IntToString(const int & value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
};
//---------------------------------------------------------------------------



void aboutinit()
{

   uv_main::about=uv_window::make_attribut(&uv_main::mainwindow,200,200,600,230,"","","","",0,0,1,0);
//   uv_main::about = uv_window::make_attribut(&uv_main::mainwindow, 200, 200, 500, 150, "", "", "", "windowdesign.tga", false, false, true, false);
	uv_main::about.set_visible(0);
	uv_main::aba=uv_text::make_attribut(&uv_main::about, 20, 40, 540, 50, 20, "Text", "Benny Loeffel, Programmierung", "Test.ttf",uv_color::make_color(255,255,255));
	uv_main::abb=uv_text::make_attribut(&uv_main::about, 20, 60, 540, 50, 20, "Text", "Lukas Humbel, Programmierung", "Test.ttf",uv_color::make_color(255,255,255));
	uv_main::abc=uv_text::make_attribut(&uv_main::about, 20, 80, 540, 50, 20, "Text", "Tugrul Guenes, GFX", "Test.ttf",uv_color::make_color(255,255,255));
	uv_main::abd=uv_text::make_attribut(&uv_main::about, 20, 80, 540, 50, 20, "Text", "4D 4Gewinnt wurde gemacht von:", "Test.ttf",uv_color::make_color(255,255,255));
	
   uv_main::abd.set_pos((uv_main::about.get_w()-uv_main::abd.get_width())/2, 50);
   uv_main::aba.set_pos((uv_main::about.get_w()-uv_main::aba.get_width())/2, 90);
   uv_main::abb.set_pos((uv_main::about.get_w()-uv_main::abb.get_width())/2, 120);
   uv_main::abc.set_pos((uv_main::about.get_w()-uv_main::abc.get_width())/2, 150);

	uv_main::aclose = uv_button::make_attribut(&uv_main::about,(600-150)/2 , 180, 150, 40, "b", "OK","");
	uv_main::aclose.set_callback((voidcallback)aboutclosecb);


}


void aboutcallback()
{
	uv_main::about.set_visible(1,1);	
   uv_main::mainwindow.set_on_top_widget(&uv_main::about);
}

void aboutclosecb()
{
	uv_main::about.set_visible(0);
	uv_main::mainwindow.set_on_top_widget(0);

}




