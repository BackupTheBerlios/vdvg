//---------------------------------------------------------------------------
// File:       uv_group.cpp
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#include "uv_group.h"
//---------------------------------------------------------------------------
uv_group::uv_group(int mx, int my, int mw, int mh,uv_group *parent,
                   char *mlabel, bool CanHaveFocus)
        :uv_widget(mx, my, mw, mh,parent,mlabel,CanHaveFocus)
{
    next_child = false;
};
//---------------------------------------------------------------------------
uv_group::attribute uv_group::make_attribut(uv_group * parent,
                                            int x, int y, int width, int height,
                                            string label, bool can_focus_have)
{
   attribute attr;
   attr.parent = parent;
   attr.x = x; attr.y = y; attr.width = width; attr.height = height;
   attr.label = label; attr.can_focus_have = can_focus_have;

   return attr;
};
//---------------------------------------------------------------------------
void uv_group::add_child(uv_widget *widget)
{
    childs.pushb(widget);
};
//---------------------------------------------------------------------------
void uv_group::remove_child(uv_widget *widget)
{
   for(int i=0; i<childs.Elemente(); i++)
   {
      if(childs.outpos(i)==widget)
      {
         childs.poppos(i);
         break;
      }
   };
};
//---------------------------------------------------------------------------
void uv_group::add_child_in_front(uv_widget *widget)
{
    childs.pushf(widget);
};
//---------------------------------------------------------------------------
void uv_group::set_start_child()
{
    childs.setiterator(0);
    if(childs.Elemente()>0)
        next_child = true;
    else
        next_child = false;
};
//---------------------------------------------------------------------------
void uv_group::set_end_child()
{
    childs.setiterator(childs.Elemente()-1);
    if(childs.Elemente()>0)
        last_child = true;
    else
        last_child = false;
};
//---------------------------------------------------------------------------
uv_widget* uv_group::get_next_child()
{
    if(!next_child)
        return NULL;
    uv_widget* child = childs.outiterator();
    if(childs.setiterator(childs.getiterator()+1))
        return child;
    else
    {
        next_child = false;
        return child;
    }
};
//---------------------------------------------------------------------------
uv_widget* uv_group::get_last_child()
{
    if(!last_child)
        return NULL;
    uv_widget* child = childs.outiterator();
    if(childs.setiterator(childs.getiterator()-1))
        return child;
    else
    {
        last_child = false;
        return child;
    }
};
//---------------------------------------------------------------------------
void uv_group::mouse_move_rel(int rel_x, int rel_y)
{
    uv_widget *child;
    set_start_child();
    while((child=get_next_child()) != NULL)
    {
        child->mouse_move_rel(rel_x,rel_y);
    };
};
//---------------------------------------------------------------------------
void uv_group::set_to_end()
{
    if(!last_child)
        childs.move(childs.getiterator(), childs.Elemente()-1);
    else
        childs.move(childs.getiterator()+1, childs.Elemente()-1);
};
//---------------------------------------------------------------------------
bool uv_group::draw_childs(vector<GLuint> * clist)
{
    //Speicher für einen uv_widget Zeiger anlegen
    uv_widget *child;
    //Den Iterator auf den Startwert von Unten setzen, da die unteren Objekte
    //zuerst gezeichnet werden
    set_start_child();
    //Die zeichenfunktion jedes childs aufrufen
    while((child=get_next_child()) != NULL)
    {
        //Farbe auf weiss zurücksetzen
        //glColor3f(1, 1, 1);
        //Draw Funktion des Childs aufrufen
        child->draw(clist);
    };
    return true;
};
//---------------------------------------------------------------------------
bool uv_group::mouse_action_childs(int x, int y, int button, int what)
{
    uv_widget *child;
    set_end_child();
    while((child=get_last_child()) != NULL)
    {
        if(child->get_x() < x &&
                child->get_y() < y &&
                (child->get_x()+child->get_w()) > x &&
                (child->get_y()+child->get_h()) > y)
        {
            bool focus = child->mouse_action(x-(child->get_x()),
                                             y-(child->get_y()), button, what);
            if(focus&&child->kann_focus_haben()&&what==SDL_MOUSEBUTTONDOWN)
            {
                set_to_end();
            }
            if(child->kann_focus_haben())
                break; //Da nur ein Objekt den Klick erhalten kann
        }
        if(what==SDL_MOUSEBUTTONUP) //Damit nur bei ursprünglichem Widget up
            break;
    };
	uv_widget::mouse_action(x,y,button,what);
    return true;
};
//---------------------------------------------------------------------------
bool uv_group::mouse_move_rel_childs(int rel_x, int rel_y)
{
    uv_widget *child;
    set_end_child();
    while((child=get_last_child()) != NULL)
    {
        child->mouse_move_rel(rel_x, rel_y);
    };

    return true;
};
//---------------------------------------------------------------------------
bool uv_group::key_action_childs(int key, int sym, int mod, int what)
{
   (childs.outpos(childs.Elemente()-1))->key_action(key, sym, mod, what);
	return 1;
};
//---------------------------------------------------------------------------
void uv_group::set_mouse_over_off()
{
    uv_widget *child;
    set_end_child();
    while((child=get_last_child()) != NULL)
    {
        child->set_mouse_over_off();
    };
    uv_widget::set_mouse_over_off();
}
//---------------------------------------------------------------------------
bool uv_group::set_focus(uv_widget * widgetpointer)
{
   for(int i=0;i<childs.Elemente();i++)
   {
      if(widgetpointer == childs.outpos(i))
      {
         childs.poppos(i);
         childs.pushb(widgetpointer);
      }
   };
   return true;
};
//---------------------------------------------------------------------------
bool uv_group::set_in_front(uv_widget * widgetpointer)
{
   for(int i=0;i<childs.Elemente();i++)
   {
      if(widgetpointer == childs.outpos(i))
      {
         childs.poppos(i);
         childs.pushf(widgetpointer);
      }
   };
   return true;
};
//---------------------------------------------------------------------------
