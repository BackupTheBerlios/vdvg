//---------------------------------------------------------------------------
// File:       uv_text.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_text.h"
//---------------------------------------------------------------------------
uv_text::uv_text():uv_widget(0, 0, 0, 0, 0, "")
{
   red=0xff;
   blue=0xff;
   green=0xff;
   len = 10001;

   bbreiteninit = false;

   //Display-Listen Zeugs:
   if(!(stranslation = glGenLists(3)))
      return; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   redraw = true;
   retranslate = true;
   last_abs_x = -1; last_abs_y = -1;
}
//---------------------------------------------------------------------------
uv_text::~uv_text()
{
   if(bbreiteninit == true)
      delete[] bbreiten;
};
//---------------------------------------------------------------------------
bool uv_text::initialize(attribute init)
{
   set_parent(init.parent);
   uv_widget::set_size(init.x, init.y, init.width, init.height);
   set_color(init.font_color.red, init.font_color.green, init.font_color.blue);
   uv_text::init(init.font.c_str(), init.font_size);
   pushtext(init.text);

   redraw = true;
   retranslate = true;
   last_abs_x = -1; last_abs_y = -1;

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
// sie eine Displayliste für das Zeichen ch, welches der Funktion ebenfalls
// übergeben wird.
void uv_text::make_dlist(FT_Face face, unsigned char ch, GLuint list_base, GLuint * tex_base)
{
   // Als erstes holen wir FreeType um unser Zeichen in ein
   // Bitmap zu rendern. Das benötigt ein paar FreeType Befehle:

   //if(ch > 128) return;

   // Lade den Glyphen unseres Zeichens
   if(FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
      cout << "FT_Load_Glyph failed";

   // bewege die Frontseite des Glyphen in ein Glyph Objekt
   FT_Glyph glyph;
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
         expanded_data[2*(i+j*width)] = expanded_data[2*(i+j*width)+1] =
                                        (i>=bitmap.width || j>=bitmap.rows)
                                        ? 0 : bitmap.buffer[i + bitmap.width*j];
      };
   };

   // Nun initialisieren wir einfach ein Paar Textur Parameter.
   glBindTexture( GL_TEXTURE_2D, tex_base[ch]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

   // als erstes müssen wir uns etwas nach oben bewegen, so dass
   // die Zeichen die richtige Menge Platz zwischen
   // und vor den Zeichen haben.
   glTranslatef(bitmap_glyph->left, 0, 0);

   // Nun bewegen wir uns etwas nach unten, für den Fall, dass
   // das Bitmap über die untere Linie geht
   // Das ist nur für Zeichen wir 'g' oder 'y' der Fall.
   glPushMatrix();
   glTranslatef(0,-1*(bitmap_glyph->top-bitmap.rows),0);

   // Nun müssen wir etwas korrigieren, da vieles unserer Textur
   // einfach nur leerer aufgefüllter Platz ist.
   // Wir finden heraus, welche Teile der Textur vom eigentlichen
   // Zeichen verwendet werden und speichern die Informationen in den
   // Variablen x und y, dann zeichnen wir den Quad
   // Quad, wir werden nur die Teile der Textur referenzieren, welche
   // das eigentliche Zeichen enthält.
   float x=(float)bitmap.width / (float)width,
         y=(float)bitmap.rows  / (float)height;

   // Hier zeichnen wir die texturierten Quads.
   // Das Bitmap welches wir von FreeType erhalten haben, ist nicht ganz
   // so ausgerichtet wie wir es gerne hätten,
   // aber wir linken die Textur auf den Quad
   // Auf diese Weise wird das Ergebniss korrekt ausgerichtet.
   glBegin(GL_QUADS);
      glTexCoord2d(0,y); glVertex2f(0,0);
      glTexCoord2d(0,0); glVertex2f(0,-bitmap.rows);
      glTexCoord2d(x,0); glVertex2f(bitmap.width,-bitmap.rows);
      glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
   glEnd();
   glPopMatrix();

   //Bei der distanzberechnung ist eine Korrektur für sehr nahe beieinander-
   //liegende Glyphen eingebaut.
   
  // glTranslatef(face->glyph->advance.x >> 6,0,0);
  // if(face->glyph->metrics.horiAdvance < (0.6)*face->glyph->metrics.width)
   //{
    // glTranslatef((face->glyph->metrics.width) >> 6, 0, 0);
   //}
   //else
   //{
     glTranslatef(face->glyph->metrics.horiAdvance >> 6, 0, 0);
   //}

   // Inkrementiere die Raster Position so, als ob wir ein Bitmap Font wären.
   // (wird nur benötigt, wenn Sie die Text Länge berechnen wollen)
   glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

   // Beende die Displayliste
   glEndList();
}
//---------------------------------------------------------------------------
bool uv_text::init(const char * fname, unsigned int h)
{
   //Wie viele Zeichen sollen erstellt werden?
   int anzahl_zeichen = 256;

   //Prüfen, ob diese Schrift bereits geladen ist...
   this->h=h;
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
   FT_Library library;
   if(FT_Init_FreeType(&library))
   {
      cout << "FT_Init_FreeType failed";
      return 0;
   }

   // Das Objekt in welchem FreeType die Informationen über den
   // Font speichert, wird ein "face" (eine Seite/Gesicht...) genannt.
   FT_Face face;

   // Hier laden wir die Font Informationen aus der Datei.
   // Von allen Möglichkeiten, wo der Code fehl schlagen könnte, ist die hier
   // die wahrscheinlichste, da FT_New_Face fehl schlagen wird, wenn die Font
   // Datei nicht existiert oder irgendwie beschädigt ist.
   if(FT_New_Face(library, fname, 0, &face))
   {
      cout << "FT_New_Face failed (there is probably a problem with your font file)";
      return 0;
   }

   // aus unerklärlichen Gründen ist die Masseinheit der Font Größe in Freetype in
   // 1/64tel Pixeln angegeben. Deshalb müssen wir, wenn wir einen Font
   // h Pixel hoch haben wollen, die Größe auf h*64 anpassen.
   // (h << 6 ist lediglich ein hübscherer Weg h*64 zu schreiben)
   //FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);
   //Höhe in Pixel
   FT_Set_Pixel_Sizes(face, h, h);

   // hier fragen wir OpenGL an, Ressourcen für all die 
   // Texturen und Display-Listen die wir
   // erzeugen wollen, zu allozieren.
   list_base=glGenLists(anzahl_zeichen);
   glGenTextures(anzahl_zeichen, textures);

   //Die charmap muss geändert werden um Umlaute zu benutzen...
//   find_unicode_charmap(face); //Ist irgendwie nicht nötig???

   // Hier erzeugen wir die einzelnen Fonts Display-Listen.
   for(int i=0;i<anzahl_zeichen;i++)
   {
      make_dlist(face, i, list_base, textures);
   };

   //Die Breiten der Glyphen abspeichern:
   bbreiten = new int[anzahl_zeichen];
   bbreiteninit = true;
   for(int i=0;i<anzahl_zeichen;i++)
   {
      FT_Load_Glyph(face, FT_Get_Char_Index(face, i), FT_LOAD_DEFAULT);
      bbreiten[i] = (face->glyph->advance.x >> 6);
   };

   // Nun, wo die Display Liste erzeugt wurde, benötigen wir die Face Informationen
   // nicht mehr, weshalb wir die damit verbundenen Ressourcen wieder freigeben.
   FT_Done_Face(face);

   // Ditto für die Font Library
   FT_Done_FreeType(library);

   //Das neue Font wurde geladen
   fontindex.insert(pair<font_set,GLuint>(temp,list_base));

   return true;
};
//---------------------------------------------------------------------------
void uv_text::clean()
{
    //
    int anzahl_zeichen = 256;

    glDeleteLists(list_base, anzahl_zeichen);
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
   //Es ist einfacher, ein anderes Koordinatensystem zu wählen,
   //da sonst die Buchstaben nicht unten sondern oben bündig werden.
   //y muss ins Koordinantensystem umgerechnet werden:
   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport); //Bildschirmgrösse abholen

   GLuint font=list_base;
   float h=this->h/.63f; // Wir machen die Höhe etwas größer. So wird es etwas
                         // Abstand zwischen den Zeilen geben.

   glDisable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_DEPTH_TEST);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glListBase(font);

   float modelview_matrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

   //This is where the text display actually happens.
   //For each line of text we reset the modelview matrix
   //so that the line's text will start in the correct position.
   //Notice that we need to reset the matrix, rather than just translating
   //down by h. This is because when each character is
   //draw it modifies the current matrix so that the next character
   //will be drawn immediatly after it.

   glColor3ub(red,green,blue); //passende Farbe laden

   int i=0;
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(x,y-h*i,0);
   glMultMatrixf(modelview_matrix);
   //  The commented out raster position stuff can be useful if you need to
   //  know the length of the text that you are creating.
   //  If you decide to use it make sure to also uncomment the glBitmap command
   //  in make_dlist().
   glRasterPos2f(0,0);
   glCallLists(line.length(), GL_UNSIGNED_BYTE, line.c_str());
   int rpos[4];
   glGetIntegerv(GL_CURRENT_RASTER_POSITION ,rpos);
   //cout << rpos[0] << endl;
   len=x-rpos[0];
   glPopMatrix();

   glBindTexture(GL_TEXTURE_2D, 0); //Texturen unbinden
   glColor3ub(0xff,0xff,0xff); //Farbe auf neutral zurÃ¼cksetzen
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
   //lines.clear();
   //lines.push_back(str);

   //Text neu zeichnen.
   redraw = true;
};
//---------------------------------------------------------------------------
void uv_text::splitup()
{
  /* lines.clear();
   int pos=0;
   int lastpos=0;

   if(lines.empty()) lines.push_back("");     */
};
//---------------------------------------------------------------------------
int uv_text::get_width()
{
   int breite = 0;
   const char * mem = line.c_str();//lines.front().c_str();
   for(int i=0; mem[i]!=0; i++)
   {
      breite += bbreiten[mem[i]];
   };
   return breite+15; //+15, Korrektur für das Font System, das irgendetwas falsch macht.
};
//---------------------------------------------------------------------------
int uv_text::get_height()
{

   return (int)h;//lines.size()*((int)h);

};
//---------------------------------------------------------------------------
void uv_text::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

   if(redraw || last_abs_x != get_absolute_x() || last_abs_y != get_absolute_y())
   {
      glTranslatef(get_absolute_x(), get_absolute_y(), 0);
      glNewList(drawing, GL_COMPILE);
         print(0, 0);
      glEndList();
      glTranslatef(-1*get_absolute_x(), -1*get_absolute_y(), 0);

      last_abs_x = get_absolute_x();
      last_abs_y = get_absolute_y();
      redraw = false;
   }

   clist->push_back(drawing);
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
