//---------------------------------------------------------------------------
//#pragma hdrstop
//#include "BeArray.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
//---------------------------------------------------------------------------
template<class temp> dstack<temp>::dstack()
{
    konstruktor();
};
//---------------------------------------------------------------------------
template<class temp> dstack<temp>::~dstack()
{
    destruktor();
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::konstruktor()
{
    m_pStart=0; m_pEnd=0;
    Enthaltene_Elemente=0;
    Iterator=0;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::destruktor()
{
    if(m_pStart!=0)
    {
        Element<temp> *Loeschen1=m_pStart;
        while(true)
        {
            Element<temp>* E=Loeschen1;
            if(Loeschen1->m_pNeachstesElement==0)
            {
                delete E;
                break;
            }
            Loeschen1=Loeschen1->m_pNeachstesElement;
            delete E;
        };
    }
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::pushf(temp wert)
{
    Element<temp> *pNeuesElement=new Element<temp>;
    pNeuesElement->m_wert=wert;
    pNeuesElement->m_pNeachstesElement=m_pStart;
    pNeuesElement->m_pVorherigesElement=0;
    if(m_pStart!=0)
        m_pStart->m_pVorherigesElement=pNeuesElement;
    m_pStart=pNeuesElement;
    if(m_pEnd==0)
        m_pEnd=pNeuesElement;
    ++Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::pushb(temp wert)
{
    Element<temp> *pNeuesElement=new Element<temp>;
    pNeuesElement->m_wert=wert;
    pNeuesElement->m_pNeachstesElement=0;
    pNeuesElement->m_pVorherigesElement=m_pEnd;
    if(m_pEnd != 0)
        m_pEnd->m_pNeachstesElement=pNeuesElement;
    m_pEnd=pNeuesElement;
    if(m_pStart==0)
        m_pStart=pNeuesElement;
    ++Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::pushpos(temp wert, long long pos)
{
    if(pos>Enthaltene_Elemente||pos<0)
    {
        return false;
    }
    if (pos == 0)
    {
        pushf(wert);
        return true;
    }
    if (pos == Enthaltene_Elemente)
    {
        pushb(wert);
        return true;
    }
    Element<temp> *pNeuesElementZeiger=m_pStart;
    Element<temp> *pNeuesElement=new Element<temp>;
    for(long long l=0;l<pos;++l)
    {
        pNeuesElementZeiger=pNeuesElementZeiger->m_pNeachstesElement;
    };
    pNeuesElementZeiger->m_pVorherigesElement->m_pNeachstesElement =
        pNeuesElement;
    pNeuesElement->m_pVorherigesElement =
        pNeuesElementZeiger->m_pVorherigesElement;
    pNeuesElementZeiger->m_pVorherigesElement=pNeuesElement;
    pNeuesElement->m_pNeachstesElement = pNeuesElementZeiger;
    pNeuesElement->m_wert = wert;
    ++Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::popf()
{
    if(m_pStart==0)
        return false;
    Element<temp> *pZuLoeschendesElement=m_pStart;
    if(m_pStart->m_pNeachstesElement!=0)
    {
        m_pStart=m_pStart->m_pNeachstesElement;
        m_pStart->m_pVorherigesElement=0;
    }
    else
    {
        m_pEnd=0;
        m_pStart=0;
    }
    delete pZuLoeschendesElement;
    --Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::popb()
{
    if(m_pEnd==0)
        return false;
    Element<temp> *pZuLoeschendesElement=m_pEnd;
    if(m_pEnd->m_pVorherigesElement!=0)
    {
        m_pEnd=m_pEnd->m_pVorherigesElement;
        m_pEnd->m_pNeachstesElement=0;
    }
    else
    {
        m_pEnd=0;
        m_pStart=0;
    }
    delete pZuLoeschendesElement;
    --Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::poppos(long long pos)
{
    if(pos+1>Enthaltene_Elemente||pos<0)
        return false;
    Element<temp> *pZuLoeschendesElement=m_pStart;
    for(long long l=0;l<pos;++l)
    {
        pZuLoeschendesElement=pZuLoeschendesElement->m_pNeachstesElement;
    };
    if(pZuLoeschendesElement->m_pNeachstesElement  !=0 &&
            pZuLoeschendesElement->m_pVorherigesElement !=0 )
    {
        pZuLoeschendesElement->m_pVorherigesElement->m_pNeachstesElement=
            pZuLoeschendesElement->m_pNeachstesElement;
        pZuLoeschendesElement->m_pNeachstesElement->m_pVorherigesElement=
            pZuLoeschendesElement->m_pVorherigesElement;
    }
    else
    {
        if(pZuLoeschendesElement->m_pNeachstesElement !=0)
        {
            pZuLoeschendesElement->m_pNeachstesElement->m_pVorherigesElement = 0;
            m_pStart=pZuLoeschendesElement->m_pNeachstesElement;
        }
        if(pZuLoeschendesElement->m_pVorherigesElement !=0)
        {
            pZuLoeschendesElement->m_pVorherigesElement->m_pNeachstesElement = 0;
            m_pEnd=pZuLoeschendesElement->m_pVorherigesElement;
        }
        if(pZuLoeschendesElement->m_pVorherigesElement == 0 &&
                pZuLoeschendesElement->m_pNeachstesElement  == 0)
        {
            m_pStart = 0; m_pEnd = 0;
        }
    }
    delete pZuLoeschendesElement;
    --Enthaltene_Elemente;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::popall()
{
    if(!destruktor())
        return false;
    if(!konstruktor())
        return false;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> temp dstack<temp>::top()
{
    if(m_pStart==0)
    {
        temp newtemp;
        return newtemp;//0;
    }
    return m_pStart->m_wert;
};
//---------------------------------------------------------------------------
template<class temp> temp dstack<temp>::bottom()
{
    if(m_pEnd==0)
    {
        temp newtemp;
        return newtemp;//0;
    }
    return m_pEnd->m_wert;
};
//---------------------------------------------------------------------------
template<class temp> temp dstack<temp>::outpos(long long pos)
{
    if(pos+1>Enthaltene_Elemente||pos<0)
    {
        temp newtemp;	
        return newtemp;//0; hmm, hmm, hmm....
    }
    Element<temp> *Ausgabeelement=m_pStart;
    for(long long l=0;l<pos;++l)
    {
        Ausgabeelement=Ausgabeelement->m_pNeachstesElement;
    };
    return Ausgabeelement->m_wert;
};
//---------------------------------------------------------------------------
template<class temp> temp dstack<temp>::outiterator()
{
    return outpos(Iterator);
};
//---------------------------------------------------------------------------
template<class temp> long long dstack<temp>::Elemente()
{
    return Enthaltene_Elemente;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::empty()
{
    return m_pStart == 0;
};
//---------------------------------------------------------------------------
template<class temp> long long dstack<temp>::getiterator()
{
    return Iterator;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::setiterator(long long iter)
{
    if(iter>=Enthaltene_Elemente||iter<0)
        return false;
    Iterator = iter;
    return true;
};
//---------------------------------------------------------------------------
template<class temp> bool dstack<temp>::move(long long from, long long to)
{
    if(from>=Enthaltene_Elemente||from<0||to>=Enthaltene_Elemente||to<0)
        return false;
    temp memory = outpos(from);
    poppos(from);
    pushpos(memory, to);
    return true;
};
//---------------------------------------------------------------------------
