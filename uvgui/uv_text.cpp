//---------------------------------------------------------------------------
// File:       uv_text.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_text.h"
//---------------------------------------------------------------------------
uv_text::uv_text()
{
   //Noch nicht initialisiert
   is_init = false;
}
//---------------------------------------------------------------------------
uv_text::~uv_text()
{
   if(bbreiteninit == true)
      delete[] bbreiten;
   // Nun, wo die Display Liste erzeugt wurde, benötigen wir die Face Informationen
   // nicht mehr, weshalb wir die damit verbundenen Ressourcen wieder freigeben.
   FT_Done_Face(face);

   // Ditto für die Font Library
   FT_Done_FreeType(library);
};
//---------------------------------------------------------------------------
bool uv_text::initialize(attribute init)
{
   red=0xff;
   blue=0xff;
   green=0xff;
   len = 10001;

   bbreiteninit = false;

   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(3)))
      return false; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   redraw = true;
   retranslate = true;
   last_abs_x = -1; last_abs_y = -1;

   uv_widget::initialize(uv_widget::make_attribut(init.parent, init.x, init.y,
                         init.width, init.height, init.name, false));
   set_color(init.font_color.red, init.font_color.green, init.font_color.blue);
   uv_text::init(init.font.c_str(), init.font_size);
   pushtext(init.text);

   draw_cursor = false;

   redraw = true;
   retranslate = true;
   last_abs_x = -1; last_abs_y = -1;

   //Initialisierung erfolgt
   is_init = true;

   return true;
};
//---------------------------------------------------------------------------
uv_text::attribute uv_text::make_attribut(uv_group * parent,
                                          int x, int y, int width, int height,
                                          int font_size,
                                          string name, string text,
                                          string font, uv_color font_color)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.font_size = font_size;
   attr.name = name; attr.text = text; attr.font = font;
   attr.font_color = font_color;

   return attr;
};
//---------------------------------------------------------------------------
// Dieser Funktion wird ein FT_Face Objekt übergeben, welches von FreeType dazu
// verwendet wird Informationen über einen Font zu speichern. Damit erstellt
// sie eine Displayliste für das Zeichen "ch", welches der Funktion ebenfalls
// übergeben wird.
void uv_text::make_dlist(FT_Face face, unsigned char ch, GLuint list_base, GLuint * tex_base)
{
   // Als erstes holen wir FreeType um unser Zeichen in ein
   // Bitmap zu rendern. Das benötigt ein paar FreeType Befehle:

   // Lade den Glyphen unseres Zeichens
   if(FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
      cout << "FT_Load_Glyph failed";

   // Nun extrahieren wir das Glyph-Image aus dem Face Objekt
   FT_Glyph glyph; // Handle für das Glyph-Image
   if(FT_Get_Glyph(face->glyph, &glyph))
      cout << "FT_Get_Glyph failed";

   // konvertiere den Glyphen in ein Bitmap
   FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
   FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

   // Diese Referenz wird es einfacher machen, auf das Bitmap zuzugreifen.
   FT_Bitmap& bitmap=bitmap_glyph->bitmap;

   // Benutze unsere Helfer-Funktion, um die Breiten der
   // Bitmap Daten zu ermitteln, die wir benötigen, um unsere
   // Texturen zu erzeugen.
   int width = next_p2(bitmap.width);
   int height = next_p2(bitmap.rows);

   // Alloziere Speicher für die Textur-Daten.
   GLubyte* expanded_data = new GLubyte[2 * width * height];

   // Hier füllen wir die Daten für das erweiterte Bitmap.
   // Beachten Sie, dass wir ein zwei Channel Bitmap verwenden (einen
   // Durchsichtigkeit und einen für Alpha), aber wir wenden beide
   // Durchsichtigkeit und Alpha auf den Wert an, den wir im
   // FreeType Bitmap finden.
   // Wir verwenden den ?: Operator, um mitzuteilen, dass wir den Wert, den wir verwenden
   // entweder 0 sein wird, wenn wir in der Auffüll-Zone sind oder aber,
   // dass es ansonsten der Wert aus dem FreeType Bitmap sein wird.
   for(int j=0; j <height;j++)
   {
      for(int i=0; i < width; i++)
      {
         expanded_data[2*(i+j*width)]   = 255;
         expanded_data[2*(i+j*width)+1] = (i>=bitmap.width || j>=bitmap.rows) ?
                                          0 : bitmap.buffer[i + bitmap.width*j];

      };
   };

   // Nun initialisieren wir einfach ein Paar Textur Parameter.
   glBindTexture( GL_TEXTURE_2D, tex_base[ch]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //Ist mir noch nicht ganz klar
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // "   "    "    "     "    "

   // Hier erzeugen wir die eigentlich Textur, beachten Sie,
   // dass wir GL_LUMINANCE_ALPHA verwenden, um zu indizieren, dass
   // wir 2 Channel Daten verwenden.
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

   // Nachdem wir die Textur erzeugt haben, benötigen wir die erweiterten
   // Daten nicht mehr.
   delete [] expanded_data;

   // Nun haben wir den Font in ein Bitmap und danach in eine OpenGl Textur
   // gerendert, und wir können nun mit dem erstellen der Displaylisten fort-
   // fahren:

   // Die Displayliste erstellen
   glNewList(list_base+ch, GL_COMPILE);

   glBindTexture(GL_TEXTURE_2D,tex_base[ch]);
   glPushMatrix();

   // als erstes müssen wir uns etwas nach vorne bewegen, so dass die Zeichen
   // die richtige Menge Platz zwischen und vor den Zeichen haben.
   glTranslatef(bitmap_glyph->left, 0, 0);

   // Nun bewegen wir uns etwas nach unten, für den Fall, dass
   // das Bitmap über die untere Linie geht
   // Das ist nur für Zeichen wir 'g' oder 'y' der Fall.
   glTranslatef(0,-1*(bitmap_glyph->top-bitmap.rows),0);  //Warum * -1 ??

   // Nun müssen wir etwas korrigieren, da vieles unserer Textur
   // einfach nur leerer aufgefüllter Platz ist.
   // Wir finden heraus, welche Teile der Textur vom eigentlichen
   // Zeichen verwendet werden und speichern die Informationen in den
   // Variablen x und y, dann zeichnen wir den Quad
   // Quad, wir werden nur die Teile der Textur referenzieren, welche
   // das eigentliche Zeichen enthält.
   double x=(double)bitmap.width / (double)width,
          y=(double)bitmap.rows  / (double)height;

   // Hier zeichnen wir die texturierten Quads.
   // Das Bitmap welches wir von FreeType erhalten haben, ist nicht ganz
   // so ausgerichtet wie wir es gerne hätten,
   // aber wir linken die Textur auf den Quad
   // Auf diese Weise wird das Ergebniss korrekt ausgerichtet.
   glBegin(GL_QUADS);
      glTexCoord2d(0, y); glVertex2f(0, 0);
      glTexCoord2d(0, 0); glVertex2f(0, -bitmap.rows);
      glTexCoord2d(x, 0); glVertex2f(bitmap.width, -bitmap.rows);
      glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
   glEnd();
   glPopMatrix();
   glTranslatef(face->glyph->metrics.horiAdvance >> 6, 0, 0);

   // Beende die Displayliste
   glEndList();

   bbreiten[ch] = (face->glyph->metrics.horiAdvance >> 6);
}
//---------------------------------------------------------------------------
bool uv_text::init(const char * fname, unsigned int h)
{
   //Wie viele Zeichen sollen erstellt werden?
   int anzahl_zeichen = 256;

   //Prüfen, ob diese Schrift bereits geladen ist...
   this->font_height=h;
   font_set temp;
   temp.filename = fname;
   temp.size = h;
   static map<font_set,GLuint> fontindex;
   map<font_set,GLuint>::iterator ite;
   ite = fontindex.find(temp);
//   if ( ite != fontindex.end()) //Dieses font_set wird bereits verwendet...
//   {
//      list_base = ite->second; //Laden
//      return 1;
//   }

   // Alloziere etwas Speicher um die Textur IDs zu speichern.
   textures = new GLuint[anzahl_zeichen];

   // erzeuge und initialisiere eine FreeType Font Library
   if(FT_Init_FreeType(&library))
   {
      //Initialisierung fehlgeschlagen!
      cout << "FT_Init_FreeType failed";
      return 0;
   }

   // Hier laden wir die Font Informationen aus der Datei.
   // Von allen Möglichkeiten, wo der Code fehl schlagen könnte, ist die hier
   // die wahrscheinlichste, da FT_New_Face fehl schlagen wird, wenn die Font
   // Datei nicht existiert oder irgendwie beschädigt ist (beziehungsweise das
   // Font-Format nicht unterstützt wird).
   // Der dritte Parameter von FT_New_Face, der "face_index", gibt an, welches
   // face geladen werden soll, falls im Font-File mehrere Faces enthalten sind.
   // Hier wird immer der Index 0 verwendet, welcher immer funktioniert.
   if(FT_New_Face(library, fname, 0, &face))
   {
      //Laden der Font Informationen fehlgeschlagen!
      cout << "FT_New_Face failed (there is probably a problem with your font file)";
      return 0;
   }

   // Nun ermitteln wir, wie viele Faces das Font-File enthält
   // Vorerst verzichten wir darauf, eventuell weitere Faces zu laden
   anzahl_faces = face->num_faces;

   // Aus unerklärlichen Gründen ist die Masseinheit der Font Größe in Freetype
   // in 1/64tel Points angegeben (1 Point == 1/27 Inch). Deshalb müssen wir,
   // wenn wir einen Font h Pixel hoch haben wollen, die Größe auf h*64 anpassen.
   // (h << 6 ist lediglich ein hübscherer Weg h*64 zu schreiben)
   // Achtung: Hier werden noch keine Fixed-Size Fonts berücksichtigt
   FT_Set_Char_Size(face, h << 6, h << 6, 72, 72);

   // Hier fragen wir OpenGL an, Ressourcen für all die Texturen und
   // Display-Listen die wir erzeugen wollen, zu allozieren.
   list_base = glGenLists(anzahl_zeichen+12); //Die letzten 12 werden für Translations benutzt
   glGenTextures(anzahl_zeichen, textures);

   //Die charmap muss geändert werden um Umlaute zu benutzen...
   // find_unicode_charmap(face); //Ist irgendwie nicht nötig???

   //Hier überprüfen wir, ob unsere Font kerning unterstützt.
   kerning_support = FT_HAS_KERNING(face);

   //Die Breiten der Glyphen abspeichern:
   bbreiten = new long[anzahl_zeichen];
   bbreiteninit = true;

   // Hier erzeugen wir die einzelnen Fonts Display-Listen.
   for(int i=0;i<anzahl_zeichen;i++)
   {
      make_dlist(face, i, list_base, textures);
   };

   // Hier erzeugen wir die Display-Listen für die Translationen.
   for(int i=0;i<12;i++)
   {
      //Das ganze eventuell noch in eine eigene Funktion auslagern...
      glNewList(list_base+anzahl_zeichen+i, GL_COMPILE);
         int x_motion;
         switch(i)
         {
            case 0:
               x_motion = 1;
               break;
            case 1:
               x_motion = 5;
               break;
            case 2:
               x_motion = 10;
               break;
            case 3:
               x_motion = 50;
               break;
            case 4:
               x_motion = 100;
               break;
            case 5:
               x_motion = 500;
               break;
            case 6:
               x_motion = -1;
               break;
            case 7:
               x_motion = -5;
               break;
            case 8:
               x_motion = -10;
               break;
            case 9:
               x_motion = -50;
               break;
            case 10:
               x_motion = -100;
               break;
            case 11:
               x_motion = -500;
               break;
         };
         glTranslatef(x_motion, 0, 0);
      glEndList();
   };

   //Das neue Font wurde geladen
   fontindex.insert(pair<font_set,GLuint>(temp,list_base));

   return true;
};
//---------------------------------------------------------------------------
void uv_text::clean()
{
    //
    int anzahl_zeichen = 256;

    glDeleteLists(list_base, anzahl_zeichen+12);
    glDeleteTextures(anzahl_zeichen ,textures);
    delete [] textures;

}
//---------------------------------------------------------------------------
void uv_text::pop_projection_matrix()
{
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
};
//---------------------------------------------------------------------------
void uv_text::print(int x, int y)
{
   //Den String zur Ausgabe vorbereiten:
   FT_UInt previous = 0; //Den vorherigen Glyph auf 0 setzen.
   FT_UInt glyph_index;  //Der momentane Glyph.
   vector<GLuint> textlist;
   for(int i=0;i<line.length();i++)
   {
      //Den jetztigen Glyph laden
      glyph_index = FT_Get_Char_Index(face, line[i]);

      //Prüfen ob Kerning durchgeführt wird.
      if(kerning_support && previous && glyph_index)
      {
         FT_Vector delta;
         FT_Get_Kerning(face, previous, glyph_index,
                        FT_KERNING_DEFAULT, &delta);
         int xmotion = delta.x >> 6;

         if(xmotion != 0)
            int a = 3;

         //Die entsprechenden Display-Listen einfügen:
         for(int z=0; z<(xmotion/500); z++)
         {
            textlist.push_back(256+5);
         };
         xmotion %= 500;
         for(int z=0; z<(xmotion/100); z++)
         {
            textlist.push_back(256+4);
         };
         xmotion %= 100;
         for(int z=0; z<(xmotion/50); z++)
         {
            textlist.push_back(256+3);
         };
         xmotion %= 50;
         for(int z=0; z<(xmotion/10); z++)
         {
            textlist.push_back(256+2);
         };
         xmotion %= 10;
         for(int z=0; z<(xmotion/5); z++)
         {
            textlist.push_back(256+1);
         };
         xmotion %= 5;
         for(int z=0; z<(xmotion); z++)
         {
            textlist.push_back(256+0);
         };
         if(xmotion < 0) xmotion *= -1;
         for(int z=0; z<(xmotion/500); z++)
         {
            textlist.push_back(256+11);
         };
         xmotion %= 500;
         for(int z=0; z<(xmotion/100); z++)
         {
            textlist.push_back(256+10);
         };
         xmotion %= 100;
         for(int z=0; z<(xmotion/50); z++)
         {
            textlist.push_back(256+9);
         };
         xmotion %= 50;
         for(int z=0; z<(xmotion/10); z++)
         {
            textlist.push_back(256+8);
         };
         xmotion %= 10;
         for(int z=0; z<(xmotion/5); z++)
         {
            textlist.push_back(256+7);
         };
         xmotion %= 5;
         for(int z=0; z<(xmotion); z++)
         {
            textlist.push_back(256+6);
         };
      };

      //Den Buchstaben einfügen
      textlist.push_back((unsigned char)line[i]);

      previous = glyph_index;
   };
   //Den Inhalt des Vectors in ein Array schreiben:
   GLuint *listarray = new GLuint[textlist.size()];
   vector<GLuint>::const_iterator iter;
   int pi=0;
   for(iter=textlist.begin(); iter != textlist.end(); iter++)
   {
      listarray[pi++] = *iter;
   };

   glDisable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_DEPTH_TEST);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glListBase(list_base);

   // This is where the text display actually happens.
   // For each line of text we reset the modelview matrix
   // so that the line's text will start in the correct position.
   // Notice that we need to reset the matrix, rather than just translating
   // down by h. This is because when each character is
   // draw it modifies the current matrix so that the next character
   // will be drawn immediatly after it.

   glColor3ub(red,green,blue); //passende Farbe laden

   int i=0;
   glPushMatrix();
   glTranslatef(x, y, 0);
   // The commented out raster position stuff can be useful if you need to
   // know the length of the text that you are creating.
   // If you decide to use it make sure to also uncomment the glBitmap command
   // in make_dlist().
   glCallLists(textlist.size(), GL_UNSIGNED_INT, listarray);

   glPopMatrix();

   glBindTexture(GL_TEXTURE_2D, 0); //Texturen unbinden
   glColor3ub(0xff,0xff,0xff); //Farbe auf neutral zurücksetzen
};
//---------------------------------------------------------------------------
void uv_text::set_color(GLubyte red,GLubyte green,GLubyte blue)
{
   this->red=red;
   this->blue=blue;
   this->green=green;
}
//---------------------------------------------------------------------------
void uv_text::pushtext(const string str)
{
   line = str;

   redraw = true;
};
//---------------------------------------------------------------------------
void uv_text::splitup()
{
};
//---------------------------------------------------------------------------
int uv_text::get_width()
{
   int breite = 0;
   for(int i=0; i<line.length(); i++)
   {
      breite += bbreiten[(unsigned char)line[i]];
   }

   return breite; //+15, Korrektur für das Font System, das irgendetwas falsch macht.
};
//---------------------------------------------------------------------------
int uv_text::get_height()
{

   return (int)font_height;

};
//---------------------------------------------------------------------------
void uv_text::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

   if(redraw || last_abs_x != get_absolute_x() || last_abs_y != get_absolute_y())
   {
      glNewList(drawing, GL_COMPILE);
         //Markierung Zeichnen:
         if(false)
         {
            int startpos=0, endpos=0;
            for(int i=0; i<line.length() && i<0; i++)
            {
               startpos += bbreiten[(unsigned char)line[i]];
            };
            for(int i=0; i<line.length() && i<cursor_position; i++)
            {
               endpos += bbreiten[(unsigned char)line[i]];
            };
            glColor4ub(0, 255, 0, 255);
            glBegin(GL_QUADS);
               glVertex2f(get_x()+startpos, get_y()-font_height);
               glVertex2f(get_x()+startpos, get_y()+4);
               glVertex2f(get_x()+endpos,   get_y()+4);
               glVertex2f(get_x()+endpos,   get_y()-font_height);
            glEnd();
         }
         print(get_x(), get_y());
         //Cursor zeichnen
         if(bbreiteninit && draw_cursor)
         {
            int xcursorpos = 0;
            //Position des Cursors berechnen:
            for(int i=0; i<line.length() && i<cursor_position; i++)
            {
               xcursorpos += bbreiten[(unsigned char)line[i]];
            };
            glColor4ub(0, 0, 0, 255);
            glLineWidth(2.0f);
            glBegin (GL_LINES);
               glVertex2f (get_x()+xcursorpos, get_y()-font_height);
               glVertex2f (get_x()+xcursorpos, get_y());
            glEnd();
         }
      glEndList();

      last_abs_x = get_absolute_x();
      last_abs_y = get_absolute_y();
      redraw = false;
   }

   clist->push_back(drawing);
};
//---------------------------------------------------------------------------
bool uv_text::set_cursor(bool draw_cursor, int position)
{
   this->draw_cursor = draw_cursor;
   cursor_position = position;
};
//---------------------------------------------------------------------------
// <Function>
//    find_unicode_charmap
//
// <Description>
//    This function finds a Unicode charmap, if there is one.
//    And if there is more than one, it tries to favour the more
//    extensive one, i.e. one that supports UCS-4 against those which
//    are limited to the BMP (said UCS-2 encoding.)
//
//    This function is called from open_face() (just below), and also
//    from FT_Select_Charmap( , FT_ENCODING_UNICODE).
//
/*void uv_text::find_unicode_charmap(FT_Face face)
{
   /*FT_CharMap*  first;
   FT_CharMap*  cur;
   FT_CharMap*  unicmap = NULL;  // some UCS-2 map, if we found it

   // caller should have already checked that `face' is valid
   //FT_ASSERT(face);

   first = face->charmaps;

   if(!first)
      //return FT_Err_Invalid_CharMap_Handle;
      return;

   // the original TrueType specification(s) only specified charmap
   // formats that are capable of mapping 8 or 16 bit character codes to
   // glyph indices.
   //
   // however, recent updates to the Apple and OpenType specifications
   // introduced new formats that are capable of mapping 32-bit character
   // codes as well. And these are already used on some fonts, mainly to
   // map non-BMP Asian ideographs as defined in Unicode.
   //
   // for compatibility purposes, these fonts generally come with
   // *several* Unicode charmaps:
   //
   // - one of them in the "old" 16-bit format, that cannot access
   //   all glyphs in the font
   //
   // - another one in the "new" 32-bit format, that can access all
   //   the glyphs.
   //
   // this function has been written to always favor a 32-bit charmap
   // when found. Otherwise, a 16-bit one is returned when found
   //
   // since the `interesting' table, with id's 3,10, is normally the
   // last one, we loop backwards. This looses with type1 fonts with
   // non-BMP characters (<.0001%), this wins with .ttf with non-BMP
   // chars (.01% ?), and this is the same about 99.99% of the time!

   cur = first + face->num_charmaps;  // points after the last one

   for(;--cur >= first;)
   {
      if(cur[0]->encoding == FT_ENCODING_UNICODE)
      {
         unicmap = cur;  // record we found a Unicode charmap

         // XXX If some new encodings to represent UCS-4 are added,
         //     they should be added here.
         if((cur[0]->platform_id == TT_PLATFORM_MICROSOFT &&
             cur[0]->encoding_id == TT_MS_ID_UCS_4)       ||
            (cur[0]->platform_id == TT_PLATFORM_APPLE_UNICODE &&
             cur[0]->encoding_id == TT_APPLE_ID_UNICODE_32))
         {
            // Hurray! We found a UCS-4 charmap. We can stop the scan!
            face->charmap = cur[0];
            //return 0;
            return;
         }
      }
   };

   // We do not have any UCS-4 charmap. Sigh.
   // Let's see if we have  some other kind of Unicode charmap, though.
   if(unicmap != NULL)
   {
      face->charmap = unicmap[0];
      return; //return 0;
   }

   // Chou blanc!
   return; //return FT_Err_Invalid_CharMap_Handle;*/
/*

    FT_CharMap found = 0;
    FT_CharMap charmap;
    int n;

    for(n = 0; n < face->num_charmaps; n++)
    {
       charmap = face->charmaps[n];
       if((charmap->platform_id == 3 &&//TT_PLATFORM_MICROSOFT &&
           charmap->encoding_id == 1) ||//TT_MS_ID_UCS_4)       ||
          (charmap->platform_id == TT_PLATFORM_APPLE_UNICODE &&
           charmap->encoding_id == TT_APPLE_ID_UNICODE_32))
       {
          found = charmap;
          break;
       }
    };
    if(!found)
    {
       return;
    }
    // now, select the charmap for the face object
    face->charmap = found;
    //FT_Set_CharMap(face, found);
//    error = FT_Set_CharMap(face, found);
//    if(error)
//    { ... }
};
//--------------------------------------------------------------------------- */
