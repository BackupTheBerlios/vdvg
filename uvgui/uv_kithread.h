//---------------------------------------------------------------------------
#ifndef uv_kithreadH
#define uv_kithreadH
//---------------------------------------------------------------------------
#include "ki.h"
#include <SDL.h>
#include <SDL_thread.h>
//---------------------------------------------------------------------------
namespace ki_thread
{
   int berechnungsstatus; // 0 keine Ber., 1 Ber. l�uft, 2 Ber. beendet
   bool threadend;
   SDL_Thread * thread;

   ki::spielfeld s_feld, ki_rueckgabefeld;

   bool start_calculations(ki::spielfeld feld);
   ki::spielfeld hole_ergebnis();
   int threadFunktion(void * daten);
   bool kill_thread();
   bool check_end_of_calculations();
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------