//---------------------------------------------------------------------------
#ifndef kiH
#define kiH
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
//---------------------------------------------------------------------------
namespace ki
{
   struct spielfeld
   {
      int feld[4][4][4][4]; // 0 == leer, 1 == Spieler 1, 2 == Spieler 2
      int gewonnen;         // 0 == niemand, 1 == Sp. 1, 2 == Sp. 2
      int schwierigkeitsgrad;
      bool fehler;          // false == alles j.o., true == etwas stimmt nicht
      bool reset();
      void operator=(const spielfeld& other);
   };

   struct resultat
   {
      int x, y, z, w, bewertung;
      bool gueltig;
   };

   struct dreiint
   {
      int a, b, c;
   };

   struct alpha_beta_cutoff
   {
      int alpha, beta; //alpha == spieler1, beta == spieler2 (Computer)
      bool gueltig;

      alpha_beta_cutoff()
      {
         gueltig=false;
      };
   };

   struct point
   {
      int x;
      int y;
      int z;
      int w;
      int typ;             //0=nichts, 1=X, 2=O
      bool gueltig;

      bool operator==(point &b)
      {
         if(x == b.y && y == b.y && z == b.z && w == b.w &&
            typ == b.typ && gueltig == b.gueltig)
            return true;
         else
            return false;
      };
   };

   //Die echte KI-Funktion, die den Computerzug berechnet:
   spielfeld calculate_computer_move(spielfeld Feld);
   //Die KI-Hilfsfunktionen:
   extern int feld[4][4][4][4];    //x,y,z,w 0=leer, 1=X, 2=O
   extern int sieg;                //Hat jemand 4Gewinnt
   extern int suchtiefe;
   extern int schwierigkeitsgrad;
   extern int seed;
   extern int dimensionen;

   char typ_gegenteil(char typ);
   resultat suchebene(int sx,int sy,int sz,int sw,int st,char typ,
                      alpha_beta_cutoff abc);
                      // pos_neg gibt an, ob es die oberste Suchebene ist, oder nicht
   bool suchebene_starten(spielfeld & Feld);
   dreiint punkt_pruefen(point startpunkt, int &gewonnen, bool updaten); //updaten: 0=nein 1=ja_down 2=ja_up
   //Bewertungsfunktionen:
   bool update(point punkt, point startpunkt, bool down);
   bool bewerte_init(spielfeld & Feld);
   bool bewerte_exit(spielfeld & Feld);
   bool bewerte_update_down(point p);
   bool bewerte_update_up(point p);
   int bewerte();//int x,int y, int z, int w);
   //Bewertungsvariabeln:
   extern int wertefeld[4][4][4][4][3];
   extern int wertefeldebene[4][4][4][4][3][6];
   extern int bewertung;
   extern int tiefe;
   bool set(point startpunkt);
}
//---------------------------------------------------------------------------
#endif
