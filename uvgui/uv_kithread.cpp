//---------------------------------------------------------------------------
#include "uv_kithread.h"
//---------------------------------------------------------------------------
bool ki_thread::start_calculations(ki::spielfeld feld)
{
   if(berechnungsstatus != 0)
      return false;

   static bool init = false;
   if(!init)
   {
      thread = SDL_CreateThread(threadFunktion, NULL);
      init = true;
      threadend = false;
   }

   ki_rueckgabefeld = feld;
   berechnungsstatus = 1;

   if(thread == NULL)
      return false;
   return true;
}
//---------------------------------------------------------------------------
int ki_thread::threadFunktion(void * daten)
{
   while(!threadend)
   {
      if(berechnungsstatus == 1)
      {
         int i = ki_rueckgabefeld.feld[0][0][0][0];
         //Berechnung starten
         ki_rueckgabefeld = ki::calculate_computer_move(ki_rueckgabefeld);

         //Berechnung beendet
         berechnungsstatus = 2;
      }
      SDL_Delay(100);
   }
   return 0;
}
//---------------------------------------------------------------------------
bool ki_thread::kill_thread()
{
   threadend = true;
   SDL_WaitThread(thread, NULL);
   return true;
}
//---------------------------------------------------------------------------
bool ki_thread::check_end_of_calculations()
{
   if(berechnungsstatus == 2)
      return true;
   return false;
}
//---------------------------------------------------------------------------
ki::spielfeld ki_thread::hole_ergebnis()
{
   ki::spielfeld feld = ki_rueckgabefeld;
   berechnungsstatus = 0;
   return feld;
}
//---------------------------------------------------------------------------
bool ki::spielfeld::reset()
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
               feld[x][y][z][u] = 0;
            }
         }
      }
   }
   gewonnen = 0;
   fehler = false;
}
//---------------------------------------------------------------------------
void ki::spielfeld::operator=(const ki::spielfeld& other)
{
   if(&other != this)
   {
      for(int x=0; x<4; x++)
      {
         for(int y=0; y<4; y++)
         {
	    for (int z=0; z<4; z++)
	    {
	       for(int u=0; u<4; u++)
	       {
                  feld[x][y][z][u] = other.feld[x][y][z][u];
               }
            }
         }
      }
      gewonnen = other.gewonnen;
      fehler   = other.fehler;
   }
}
//---------------------------------------------------------------------------
 