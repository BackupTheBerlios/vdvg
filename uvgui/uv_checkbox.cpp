#include "uv_checkbox.h"

uv_checkbox::uv_checkbox()
{
   is_init = 0;
}

bool uv_checkbox::initialize(attribute init)
{
   if(!(stranslation = glGenLists(3)))
      return false; //Error !!
   drawing = stranslation+1;
   etranslation = drawing+1;

   redraw = true;
   retranslate = true;

   uv_group::initialize(uv_group::make_attribut(init.parent, init.x, init.y, init.width, init.height, init.name, true));

   uv_color text_color = {0x00, 0x00, 0x00};
   init.text_attribute.parent = this;
   text = init.text_attribute;
   text.set_pos(20, (16+text.get_height())/2-3);

   init.image_unchecked.parent = this;
   init.image_checked.parent = this;
   uncheckimage = init.image_unchecked;
   checkimage   = init.image_checked;

   redraw = true;
   retranslate = true;
	
   checked = false;
   //Initialisierung erfolgt
   is_init = true;

   return true;
};

uv_checkbox::attribute uv_checkbox::make_attribut(uv_group * parent, int x, int y,
                                  int width, int height, uv_image::attribute image_unchecked, uv_image::attribute image_checked,
                                  uv_text::attribute text_attribute, string name)
{
   attribute attr;

   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.image_unchecked = image_unchecked; attr.image_checked = image_checked;
   attr.text_attribute = text_attribute;
   attr.name = name;

   return attr;
};

void uv_checkbox::draw(vector<GLuint> * clist)
{
   if(!get_visible())
      return;

   if(retranslate)
   {
      glNewList(stranslation, GL_COMPILE);
      glTranslatef(get_x(), get_y(), 0);
      glEndList();

      glNewList(etranslation, GL_COMPILE);
      glTranslatef(-1*get_x(), -1*get_y(), 0);
      glEndList();

      retranslate = false;
   }

   if(redraw)
   {
      glNewList(drawing, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, 0);
      glBegin (GL_QUADS);
         glColor4ub (100, 100, 100, 120);
         glVertex2i (0, 0);             // Links Oben
         glVertex2i (get_w(), 0);       // Rechts Oben
         glVertex2i (get_w(), get_h()); // Rechts Unten
         glVertex2i (0, get_h());       // Links Unten
      glEnd ();
      glEndList();

      redraw = false;
   }

   clist->push_back(stranslation);
   if(checked)
   {
      uncheckimage.set_visible(false);
      checkimage.set_visible(true);
   }
   else
   {
      uncheckimage.set_visible(true);
      checkimage.set_visible(false);
   }
   if(mouse_over())
   {
      clist->push_back(drawing);
   }

   draw_childs(clist);

   clist->push_back(etranslation);
}

bool uv_checkbox::mouse_action(int x, int y,int button,int what)
{
    if( what==SDL_MOUSEBUTTONDOWN && get_visible())  //Nur reagieren, wenn der Button sichtbar ist...
    {
        callback var;
        var.ID = 12;
        do_callback(&var);
	checked = !checked;
    }
    uv_widget::mouse_action(x,y,button,what);
    return true;
}

void uv_checkbox::key_action(int key, int sym, int mod, int what)
{
   if(sym == SDLK_RETURN && what== SDL_KEYDOWN)//key == SDLK_RETURN)
   {
      callback var;
      var.ID = 12;
      do_callback(&var);
      checked = !checked;
   }
}


