/*
-----------------------------------------------------------------------------
4D 4Gewinnt is simple board game.
Copyright (C) 2004 Benny Loeffel, Lukas Humbel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
-----------------------------------------------------------------------------
*/
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
   extern int berechnungsstatus; // 0 keine Ber., 1 Ber. l�uft, 2 Ber. beendet
   extern bool threadend;
   extern SDL_Thread * thread;

   extern ki::spielfeld s_feld, ki_rueckgabefeld;

   bool start_calculations(ki::spielfeld feld);
   ki::spielfeld hole_ergebnis();
   int threadFunktion(void * daten);
   bool kill_thread();
   bool check_end_of_calculations();
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
