//---------------------------------------------------------------------------
//#pragma hdrstop
//#include "BeArray.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
//---------------------------------------------------------------------------
/*template<class temp> dstack<temp>::dstack()
{
   //konstruktor();
};
dstack::~dstack()
{
   destruktor();
};
bool dstack::konstruktor()
{
   m_pStart=0; m_pEnd=0;
   Enthaltene_Elemente=0;
   return true;
}
bool dstack::destruktor()
{
   if(m_pStart!=0)
   {
      Element *Loeschen1=m_pStart;
      while(true)
      {
         Element* E=Loeschen1;
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
}
bool dstack::pushf(int wert)
{
   Element *pNeuesElement=new Element;
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
bool dstack::pushb(int wert)
{
   Element *pNeuesElement=new Element;
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
bool dstack::pushpos(int wert, long long pos)
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
   Element *pNeuesElementZeiger=m_pStart;
   Element *pNeuesElement=new Element;
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
bool dstack::popf()
{
   if(m_pStart==0)
      return false;
   Element *pZuLoeschendesElement=m_pStart;
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
bool dstack::popb()
{
   if(m_pEnd==0)
      return false;
   Element *pZuLoeschendesElement=m_pEnd;
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
bool dstack::poppos(long long pos)
{
   if(pos+1>Enthaltene_Elemente||pos<0)
      return false;
   Element *pZuLoeschendesElement=m_pStart;
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
bool dstack::popall()
{
   if(!destruktor())
      return false;
   if(!konstruktor())
      return false;
   return true;
};
int dstack::top()
{
   if(m_pStart==0)
      return 0;
   return m_pStart->m_wert;
}
int dstack::bottom()
{
   if(m_pEnd==0)
      return 0;
   return m_pEnd->m_wert;
}
int dstack::outpos(long long pos)
{
   if(pos+1>Enthaltene_Elemente||pos<0)
      return 0;
   Element *Ausgabeelement=m_pStart;
   for(long long l=0;l<pos;++l)
   {
      Ausgabeelement=Ausgabeelement->m_pNeachstesElement;
   };
   return Ausgabeelement->m_wert;
}
long long dstack::Elemente()
{
   return Enthaltene_Elemente;
}
bool dstack::empty()
{
   return m_pStart == 0;
}*/
