#ifndef _UV_CHECKBOX_
#define _UV_CHECKBOX_

#include "uv_include.h"
#include <SDL.h>
#include <SDL_opengl.h>

class uv_checkbox: public uv_group
{
public:
   struct attribute
   {
      uv_group * parent;
      int x, y, width, height;
      uv_image::attribute image_unchecked, image_checked;
      uv_text::attribute text_attribute;
      string name;//, caption;
   };
   struct callback: public uv_callback
   {
      bool checked;
   };
private:
   bool is_init;
   bool checked;
   uv_text text;
   std::string textspeicher;
   GLuint stranslation, etranslation, drawing;
   bool redraw, retranslate;
   uv_image uncheckimage, checkimage;
public:
   uv_checkbox();
   bool get_checked() {return checked;};
   void set_checked(bool c) {checked=c;};
   bool initialize(attribute init);
   bool operator=(attribute init) {return initialize(init);};

   void draw(vector<GLuint> * clist);
   bool mouse_action(int x, int y, int button, int what);
   void key_action(int key, int sym, int mod, int what);
   static attribute make_attribut(uv_group * parent, int x, int y,
                                  int width, int height, uv_image::attribute image_unchecked, uv_image::attribute image_checked,
                                  uv_text::attribute text_attribute, string name);
};

#endif	

