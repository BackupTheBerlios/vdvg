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

