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
	ki::spielfeld& get_s_feld();
	ki::spielfeld& get_ki_rueckgabefeld();
	bool start_calculations(ki::spielfeld feld);
	ki::spielfeld hole_ergebnis();
	int threadFunktion(void * daten);
	bool kill_thread();
	bool check_end_of_calculations();
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

