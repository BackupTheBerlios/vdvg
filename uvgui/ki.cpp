//---------------------------------------------------------------------------
#include "ki.h"
//---------------------------------------------------------------------------
int ki::feld[4][4][4][4];    //x,y,z,w 0=leer, 1=X, 2=O
int ki::sieg;                //Hat jemand 4Gewinnt
int ki::suchtiefe;
int ki::schwierigkeitsgrad;
int ki::seed;
int ki::dimensionen;

int ki::wertefeld[4][4][4][4][3];
int ki::wertefeldebene[4][4][4][4][3][6];
int ki::bewertung;
int ki::tiefe;
//---------------------------------------------------------------------------
//  Die echten KI-Funktionen:
//---------------------------------------------------------------------------
// Diese Funktion verwaltet alle KI funktionen und führt die berechnung des
// Computer-Zuges durch.
ki::spielfeld ki::calculate_computer_move(ki::spielfeld Feld)
{
   //Die Suchtiefe wird momentan mit einem Fixen Wert angegeben.
   suchtiefe = 2;
   schwierigkeitsgrad = 0;
   seed = (unsigned)time(NULL);
   //Die Spielfeldbewertung initialisieren und prüfen, ob der Bewertungs-
   //baum gestartet werden kann.
   if(!bewerte_init(Feld))
   {
      //Der Bewertungsbaum kann nicht gestartet werden, entweder weil
      //bereits jemand gewonnen hat, oder im Spielfeld ein Fehler vor-
      //handen ist.
      return Feld;
   }

   //Bewertungsbaum starten
   suchebene_starten(Feld);

   //Die Spielfeldbewertung abschliessen, und das Spielfeld zurückgeben
   bewerte_exit(Feld);

   return Feld;
}
//---------------------------------------------------------------------------
bool ki::set(ki::point startpunkt)
{
   //Prüfe, ob die Koordinaten existieren, sonst return false (noch nicht n-D)
   if(!(startpunkt.x<4 && startpunkt.x>=0 && startpunkt.y<4 && startpunkt.y>=0
      && startpunkt.z<4 && startpunkt.z>=0 && startpunkt.w<4 && startpunkt.w>=0))
      return false;

   //Prüfen, ob das Feld noch frei ist, sonst return false (noch nicht n-D)
   if(feld[startpunkt.x][startpunkt.y]
          [startpunkt.z][startpunkt.w] != 0)
      return false;

   //Den Punkt setzen:
   feld[startpunkt.x][startpunkt.y]
       [startpunkt.z][startpunkt.w] = startpunkt.typ;

   //Auf Sieg überprüfen (noch nicht n-D)
   int i;
   punkt_pruefen(startpunkt, i, false);
   sieg = i;
   //Überprüfung fertig und Sieg gesetzt
   return true;
};
//---------------------------------------------------------------------------
bool ki::suchebene_starten(ki::spielfeld & Feld)
{
   point    res1;
   resultat res2;
   srand(seed);
   //Alpha-Beta Cutoff
   alpha_beta_cutoff cut;
   //Alpha will einen tiefen Wert, Beta einen hohen erreichen. Darum erhält
   //Alpha einen hohen und Beta einen tiefen Startwert.
   cut.alpha=10000000; cut.beta=-10000000; cut.gueltig=true;

   //Bewertungsbaum starten:
   res2 = suchebene(0, 0, 0, 0, suchtiefe, 2, cut); //Typ == 2, da ???

   //Auswertung übergeben
   res1.x = res2.x;
   res1.y = res2.y;
   res1.z = res2.z;
   res1.w = res2.w;
   res1.typ = 2;
   res1.gueltig = res2.gueltig;
   if(res2.bewertung==0)
      int a;

   Feld.feld[res1.x][res1.y][res1.z][res1.w] = res1.typ;
   Feld.fehler = !res1.gueltig;

   return true;
};
//---------------------------------------------------------------------------
ki::resultat ki::suchebene(int sx, int sy, int sz, int sw, int st, char typ,
                           ki::alpha_beta_cutoff cut)
{
   resultat wertmax, temp;
   wertmax.gueltig=false;
   wertmax.x=0; wertmax.y=0; wertmax.z=0; wertmax.w=0;
   //wertmax.bewertung initialisieren
   if(typ==1)
      wertmax.bewertung = +100000000;  // Will tiefen Wert erreichen
   if(typ==2)
      wertmax.bewertung = -100000000;  // Will hohen Wert erreichen
   //Bewertung updaten
   feld[sx][sy][sz][sw]=typ_gegenteil(typ);
   {
      point p={sx, sy, sz, sw, typ_gegenteil(typ), true};
      bewerte_update_down(p);
   }
   //Prüfen, ob max. Suchtiefe schon erreicht
   if(st<=0)
   {
      wertmax.bewertung = bewerte();
      wertmax.gueltig = true;
      wertmax.x=0; wertmax.y=0; wertmax.z=0; wertmax.w=0;
      point p={sx, sy, sz, sw, typ_gegenteil(typ), true};
      bewerte_update_up(p);
      feld[sx][sy][sz][sw]=0; //Ist an dieser Stelle nötig, aber wieso?
      return wertmax;
   }
   int a, b, c, d, x, y, z, w, x1,y1,z1,w1;
   a = rand()%2; b = rand()%2; c = rand()%2; d = rand()%2;
   //Jeden Punkt überprüfen
   for(x1=0;x1<4;x1++)
   {
      for(y1=0;y1<4;y1++)
      {
         for(z1=0;z1<4;z1++)
         {
            for(w1=0;w1<4;w1++)
            {
               if(a) x = x1; else x = 3-x1;
               if(b) y = y1; else y = 3-y1;
               if(c) z = z1; else z = 3-z1;
               if(d) w = w1; else w = 3-w1;

               if(feld[x][y][z][w]==0) //Punkt frei?
               {
                  //Punkt bewerten
                  temp=suchebene(x, y, z, w, st-1, typ_gegenteil(typ), cut);
                  //eventuell die neuen Alpha und Beta Werte zuweisen.
                  if(typ==1&&temp.bewertung<cut.alpha)
                     cut.alpha=temp.bewertung;
                  if(typ==2&&temp.bewertung>cut.beta)
                     cut.beta=temp.bewertung;
                  //wenn Bewertung besser als bisherige Maximalbewertung
                  if((temp.bewertung>wertmax.bewertung&&typ==2) ||
                     (temp.bewertung<wertmax.bewertung&&typ==1))
                  {
                     wertmax.bewertung=temp.bewertung;
                     wertmax.x=x;
                     wertmax.y=y;
                     wertmax.z=z;
                     wertmax.w=w;
                     wertmax.gueltig=true;
                  }
                  if(cut.alpha<=cut.beta)
                     goto endloop;
               }
            };
         };
      };
   };
   endloop:
   //Wenn kein Punkt gesetzt werden konnte, weil Feld voll
   if (wertmax.gueltig == false)
   {
      //sieg=4;
   }
   //Bewertung updaten
   {
      point p={sx, sy, sz, sw, typ_gegenteil(typ), true};
      bewerte_update_up(p);
   }
   feld[sx][sy][sz][sw]=0;
   //Resultat zurückgeben
   return wertmax;
};
//---------------------------------------------------------------------------
//Wandelt einen char typ in sein Gegenteil um
char ki::typ_gegenteil(char typ)
{
   if((int)typ==1) return 2;
   if((int)typ==2) return 1;
   return typ;
};
//---------------------------------------------------------------------------
//Bewertet das Spielfeld, muss wahrscheinlich neu geschrieben werden
int ki::bewerte()//int oldx, int oldy, int oldz, int oldw)
{
   return bewertung;
}
//---------------------------------------------------------------------------
bool ki::bewerte_init(ki::spielfeld & Feld)
{
   sieg = 0;
   dimensionen = 4;

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

   int a = 0;
   //feld in feld kopieren
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
	 for (int z=0; z<4; z++)
	 {
	    for(int u=0; u<4; u++)
	    {
               point pt; pt.x = x; pt.y = y; pt.z = z; pt.w = u;
               pt.gueltig = true; pt.typ = Feld.feld[x][y][z][u];
               if(!set(pt))
               {
                  Feld.fehler = true;
                  return false;
               }
               if(sieg != 0)
               {
                  if(!a)
                  {
                     Feld.gewonnen = sieg;
                     a++;
                  }
                  else
                  {
                     Feld.fehler = true;
                     return false;
                  }
               }
               // ....
               //feld[x][y][z][u] = Feld.feld[x][y][z][u];
            }
         }
      }
   }
   if(a)
   {
      return false;//Feld;
   }

   //Gehe jeden freien Punkt durch und bewerte ihn, anschliessen die Punkte
   //zusammenzählen und abspeichern:
   bewertung=0;
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
         for(int z=0; z<4; z++)
         {
            for(int w=0; w<4; w++)
            {
               // Prüfen, ob das Feld noch frei ist:
               if(feld[x][y][z][w]!=0) // Wenn Besetzt, dann Wertung 0 vergeben
               {
                  wertefeld[x][y][z][w][0]=0;
                  wertefeld[x][y][z][w][1]=0;
                  wertefeld[x][y][z][w][2]=0;
               }
               else
               {
                  //Diesen Punkt  bewerten
                  point p={x,y,z,w,1,true};
                  int gewonnen;
                  dreiint di = punkt_pruefen(p, gewonnen, false);
                  wertefeld[x][y][z][w][0]=di.a;
                  wertefeld[x][y][z][w][1]=di.b;
                  wertefeld[x][y][z][w][2]=di.c;
               }
               bewertung += wertefeld[x][y][z][w][0];
            };
         };
      };
   };
   tiefe=0;
   return true;
};
//---------------------------------------------------------------------------
bool ki::bewerte_exit(ki::spielfeld & Feld)
{
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

   int b = 0;
   //feld in feld kopieren
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
	 for (int z=0; z<4; z++)
	 {
	    for(int u=0; u<4; u++)
	    {
               point pt; pt.x = x; pt.y = y; pt.z = z; pt.w = u;
               pt.gueltig = true; pt.typ = Feld.feld[x][y][z][u];
               if(!set(pt))
               {
                  Feld.fehler = true;
                  return false;
               }
               if(sieg != 0)
               {
                  if(!b)
                  {
                     Feld.gewonnen = sieg;
                     b++;
                  }
                  else
                  {
                     Feld.fehler = true;
                     return false;
                  }
               }
               // ....
               //feld[x][y][z][u] = Feld.feld[x][y][z][u];
            }
         }
      }
   }
};
//---------------------------------------------------------------------------
bool ki::bewerte_update_down(ki::point p)
{
   //Momentaner stand sichern:
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
         for(int z=0; z<4; z++)
         {
            for(int w=0; w<4; w++)
            {
               for(int a=0; a<3; a++)
               {
                  wertefeldebene[x][y][z][w][a][tiefe]=wertefeld[x][y][z][w][a];
               };
            };
         };
      };
   };
   tiefe++;
   int gewonnen;
   punkt_pruefen(p, gewonnen, true);
   return true;
};
//---------------------------------------------------------------------------
bool ki::bewerte_update_up(ki::point p)
{
   bewertung=0;
   tiefe--;
   //Momentaner stand zurückspielen:
   for(int x=0; x<4; x++)
   {
      for(int y=0; y<4; y++)
      {
         for(int z=0; z<4; z++)
         {
            for(int w=0; w<4; w++)
            {
               for(int a=0; a<3; a++)
               {
                  wertefeld[x][y][z][w][a]=wertefeldebene[x][y][z][w][a][tiefe];
               };
               bewertung+=wertefeldebene[x][y][z][w][0][tiefe];
            };
         };
      };
   };
   return true;
};
//---------------------------------------------------------------------------
//Bewertet einen Punkt, positiv für Sp. 2, negativ für Sp. 1
ki::dreiint ki::punkt_pruefen(ki::point startpunkt, int &gewonnen, bool updaten)
{
   gewonnen = 0;
   if(updaten)
   {
      wertefeld[startpunkt.x][startpunkt.y][startpunkt.z][startpunkt.w][0]=0;
   }
   int rueckgabewert1=0,rueckgabewert2=0;
   dreiint rueckgabewert;
   bool tsieg=false;
   int xmove,ymove,zmove,wmove,gang;
   point punkt=startpunkt;
   int geprueft[50][4]; int zeiger=0;
   for(xmove=-1;xmove<2;xmove++)
   {
      for(ymove=-1;ymove<2;ymove++)
      {
         for(zmove=-1;zmove<2;zmove++)
         {
            for(wmove=-1;wmove<2;wmove++)
            {
               bool loop=true;
               int xdir=xmove,ydir=ymove,zdir=zmove,wdir=wmove;
               tsieg = true;
               //Ungültigen Punkt ausfiltern
               if(xmove == 0 && ymove==0 && zmove==0 && wmove==0)
               {
                  tsieg=false; //Ungültige ausfiltern
                  loop=false;
               }
               //Prüfen, ob dieser Punkt schon abgefragt wurde
               for(int j=0; j<zeiger; j++)
               {
                  if(geprueft[j][0]==xmove*-1 && geprueft[j][1]==ymove*-1 &&
                     geprueft[j][2]==zmove*-1 && geprueft[j][3]==wmove*-1)
                  {
                     tsieg=false;
                     loop=false;
                     break;
                  }
               };
               //Diesen Punkt in die Liste der geprüften aufnehmen
               if(tsieg==true)
               {
                  geprueft[zeiger][0] = xmove;
                  geprueft[zeiger][1] = ymove;
                  geprueft[zeiger][2] = zmove;
                  geprueft[zeiger][3] = wmove;
                  zeiger++;
               }
               //Weitermachen, wenn Sieg noch möglich und maximale Schrittanzahl
               //noch nicht erreicht ist.
               int i1=0, i2=0;
               for(gang=0;gang<3&&loop==true;gang++)
               {
                  punkt.x = punkt.x+xdir;
                  punkt.y = punkt.y+ydir;
                  punkt.z = punkt.z+zdir;
                  punkt.w = punkt.w+wdir;
                  //Prüfen, ob ausserhalb des gültigen Bereiches
                  if((punkt.x<0||xdir==0||punkt.x>3)&&
                     (punkt.y<0||ydir==0||punkt.y>3)&&
                     (punkt.z<0||zdir==0||punkt.z>3)&&
                     (punkt.w<0||wdir==0||punkt.w>3))
                  {
                     punkt.x = startpunkt.x; xdir *= -1; punkt.x += xdir;
                     punkt.y = startpunkt.y; ydir *= -1; punkt.y += ydir;
                     punkt.z = startpunkt.z; zdir *= -1; punkt.z += zdir;
                     punkt.w = startpunkt.w; wdir *= -1; punkt.w += wdir;
                  }
                  else
                  {
                     if(punkt.x<0||punkt.y<0||
                        punkt.z<0||punkt.w<0||
                        punkt.x>3||punkt.y>3||
                        punkt.z>3||punkt.w>3)
                     {
                        tsieg=false;
                        loop=false;
                        break;
                     }
                  }
                  //Prüfen, ob dieser Punkt vom Typ punkt.typ ist
                  if(feld[punkt.x][punkt.y]
                         [punkt.z][punkt.w] != punkt.typ)
                     tsieg=false;
                  //Diese Reihe bewerten:
                  if(feld[punkt.x][punkt.y]
                         [punkt.z][punkt.w] == 1)
                  {
                     i1++;
                  }
                  if(feld[punkt.x][punkt.y]
                         [punkt.z][punkt.w] == 2)
                  {
                     i2++;
                  }
                  if(updaten==true&&feld[punkt.x][punkt.y]
                                        [punkt.z][punkt.w] == 0)
                  {
                     update(punkt, startpunkt, true);
                  }
               };
               punkt = startpunkt;
               //Prüfen, ob jemand gewonnen hat, wenn ja Funktion beenden
               if (tsieg == true)
               {
                  gewonnen = punkt.typ;
               }
               //Achtung, noch auf loop prüfen
               int zahl=0;
               if(loop)
               {
                  //Reihe auswerten und Punkte vergeben
                  if(i1==0&&i2>0)
                     zahl = (i2==1) ?  2 : ((i2==2) ?  200 :  5000);
                  if(i1>0&&i2==0)
                     zahl = (i1==1) ? -2 : ((i1==2) ? -200 : -5000);
                  if(zahl>0)
                  {
                     //verhindert eine doppelte Dreiergruppe
                     if(rueckgabewert2>=200&&zahl>=200)
                        rueckgabewert2 += 15000;
                     rueckgabewert2 += zahl;
                  }
                  if(zahl<0)
                  {
                     if(rueckgabewert1<=-200&&zahl<=-200)
                        rueckgabewert1 -= 15000;
                     rueckgabewert1 += zahl;
                  }
                  //Testweise implementiert
                  if(updaten&&i1==3)
                  {
                     if(punkt.typ==1)
                        wertefeld[startpunkt.x][startpunkt.y]
                                 [startpunkt.z][startpunkt.w][0]=-30000;
                  }
                  if(updaten&&i2==3)
                  {
                     if(punkt.typ==2)
                        wertefeld[startpunkt.x][startpunkt.y]
                                 [startpunkt.z][startpunkt.w][0]=20000;
                  }
               }
            };
         };
      };
   };
   int rueckgabe = rueckgabewert1 + rueckgabewert2;
   /*if(rueckgabe>10000)
      rueckgabe=10000;
   if(rueckgabe<-10000)
      rueckgabe=-10000; */
   if(updaten==true)
   {
      //Gehe jeden freien Punkt durch und bewerte ihn, anschliessen die Punkte
      //zusammenzählen und abspeichern:
      bewertung=0;
      for(int x=0; x<4; x++)
      {
         for(int y=0; y<4; y++)
         {
            for(int z=0; z<4; z++)
            {
               for(int w=0; w<4; w++)
               {
                  //Diesen Punkt  bewerten
                  bewertung += wertefeld[x][y][z][w][0];
               };
            };
         };
      };
   }
   rueckgabewert.a = rueckgabe;
   rueckgabewert.b = rueckgabewert1;
   rueckgabewert.c = rueckgabewert2;
   return rueckgabewert;
};
//---------------------------------------------------------------------------
bool ki::update(ki::point punkt, ki::point startpunkt, bool down)
{
   int xdir = (punkt.x > startpunkt.x) ? -1 : ((punkt.x < startpunkt.x) ? 1 : 0);
   int ydir = (punkt.y > startpunkt.y) ? -1 : ((punkt.y < startpunkt.y) ? 1 : 0);
   int zdir = (punkt.z > startpunkt.z) ? -1 : ((punkt.z < startpunkt.z) ? 1 : 0);
   int wdir = (punkt.w > startpunkt.w) ? -1 : ((punkt.w < startpunkt.w) ? 1 : 0);
   point neu = startpunkt;
   startpunkt = punkt;
   int i1=0, i1a=0, i2=0, i2a=0, zahl=0;
   bool loop = true;
   for(int gang=0;gang<3&&loop==true;gang++)
   {
      punkt.x = punkt.x+xdir;
      punkt.y = punkt.y+ydir;
      punkt.z = punkt.z+zdir;
      punkt.w = punkt.w+wdir;
      //Prüfen, ob ausserhalb des gültigen Bereiches
      if((punkt.x<0||xdir==0||punkt.x>3)&&
         (punkt.y<0||ydir==0||punkt.y>3)&&
         (punkt.z<0||zdir==0||punkt.z>3)&&
         (punkt.w<0||wdir==0||punkt.w>3))
      {
         punkt.x = startpunkt.x; xdir *= -1; punkt.x += xdir;
         punkt.y = startpunkt.y; ydir *= -1; punkt.y += ydir;
         punkt.z = startpunkt.z; zdir *= -1; punkt.z += zdir;
         punkt.w = startpunkt.w; wdir *= -1; punkt.w += wdir;
      }
      else
      {
         if(punkt.x<0||punkt.y<0||
            punkt.z<0||punkt.w<0||
            punkt.x>3||punkt.y>3||
            punkt.z>3||punkt.w>3)
         {
            loop=false;
         }
      }
      //Diese Reihe bewerten:
      if(feld[punkt.x][punkt.y]
             [punkt.z][punkt.w] == 1)
      {
         i1++;
         if(neu==punkt)
            i1a=1;
      }
      if(feld[punkt.x][punkt.y]
             [punkt.z][punkt.w] == 2)
      {
         i2++;
         if(neu==punkt)
            i2a=1;
      }
   };
   if(loop)
   {
      //Reihe auswerten und Punkte vergeben
      int vorher=0;
      if(i1==0&&i2>0)
         zahl = (i2==1) ?  2 : ((i2==2) ?  200 :  5000);
      if(i1>0&&i2==0)
         zahl = (i1==1) ? -2 : ((i1==2) ? -200 : -5000);
      i1-=i1a;
      i2-=i2a;
      if(i1==0&&i2>0)
         vorher = (i2==1) ?  2 : ((i2==2) ?  200 :  5000);
      if(i1>0&&i2==0)
         vorher = (i1==1) ? -2 : ((i1==2) ? -200 : -5000);
      
      zahl-=vorher;
      //Problem: im wertefeld sind die Werte nicht separat gespeichert==>
      //muss noch geändert werden
      int rueckgabewert1=wertefeld[startpunkt.x][startpunkt.y]
                                  [startpunkt.z][startpunkt.w][1];
      int rueckgabewert2=wertefeld[startpunkt.x][startpunkt.y]
                                  [startpunkt.z][startpunkt.w][2];
      if(zahl>0)
      {
         if(rueckgabewert2>=200&&zahl>=200)
            rueckgabewert2 += 15000;
         rueckgabewert2 += zahl;
      }
      if(zahl<0)
      {
         if(rueckgabewert1<=-200&&zahl<=-200)
            rueckgabewert1 -= 15000;
         rueckgabewert1 += zahl;
      }
      //Achtung: Überprüft noch nicht, ob grösser/kleiner als 10'000
      wertefeld[startpunkt.x][startpunkt.y]
               [startpunkt.z][startpunkt.w][0] += zahl;
      wertefeld[startpunkt.x][startpunkt.y]
               [startpunkt.z][startpunkt.w][1] = rueckgabewert1;
      wertefeld[startpunkt.x][startpunkt.y]
               [startpunkt.z][startpunkt.w][2] = rueckgabewert2;
   }
};
//---------------------------------------------------------------------------
