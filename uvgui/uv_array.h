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
#ifndef BeArrayH
#define BeArrayH
//---------------------------------------------------------------------------
template<class temp> class dstack
{
    template<class tempa> class Element
    {
    public:
        tempa m_wert;
        Element *m_pNeachstesElement;
        Element *m_pVorherigesElement;
    };
private:
    //Zeiger das Erste, Letzte Element im Stack
    Element<temp> *m_pStart, *m_pEnd;
    //Gibt die Anzahl gespeicherter Elemente an
    long long Enthaltene_Elemente;
    long long Iterator;
    bool konstruktor();
    bool destruktor();
public:
    dstack();
    ~dstack();
    bool pushf(temp wert);
    bool pushb(temp wert);
    bool pushpos(temp wert, long long pos);
    bool popf();
    bool popb();
    bool poppos(long long pos);
    bool popall();
    temp top();
    temp bottom();
    temp outpos(long long pos);
    temp outiterator();
    long long Elemente();
    bool empty();
    long long getiterator();
    bool setiterator(long long iter);
    bool move(long long from, long long to);
};
//---------------------------------------------------------------------------
#include "uv_arraycpp.h"
//---------------------------------------------------------------------------
#endif

