//
// File: uvwidget.h
// Created by: User <Email>
// Created on: Tue Apr 13 00:07:11 2004
//

#ifndef _UV_WIDGET_H_
#define _UV_WIDGET_H_
typedef void (*voidcallback)();

class uv_widget
{
	private:
		int x,y,w,h;
		voidcallback callback;
		int whenbits;
		char *label;
		bool visible;
	
	public:
		uv_widget(int mx, int my, int mw, int mh, char *mlabel=0) //setzt Variabeln,Konstruktor, sollte irgendwie protected sein...
			{x=mx;y=my;w=mw;h=mh;label=mlabel;}
		virtual ~uv_widget(){};									//Macht nichts.
		int get_w() 									//Liefert die breite (width)
			{return w;}
		int get_h() 									//Liefert die Hoehe (height)
			{return h;}
		int get_x() 									//Liefert die x Koordinate
			{return x;}
		int get_y() 									//Liefert die y Koordinate
			{return y;}
	    bool set_size(int mx, int my, int mw, int mh)  	//Gr�sse eines Widgets ver�ndern
			{x=mx;y=my;w=mw;h=mh;return 1;}
		virtual void draw()=0;											//Zeichnet das Widget
		void set_callback( voidcallback cb)	//Setz einen Funktionszeiger für Callback
			{callback=cb;}
		voidcallback get_callback()						//Callback Adresse zurückgeben
			{return callback;}
		void set_when (int bitset)						//Wann wird der Callback ausgelöst?
			{whenbits=bitset;}											//Bitmasken werden ueber Defines gesetzt.
	   	char* get_label()								//Label zurueckgeben
			{return label;}
		void set_visible(bool vis)						//wenn visible=0, nicht zeichnen
			{visible=vis;}
	 	bool get_visible()									//visible?
			{return visible;}
		virtual void key_action(char key)=0;
		virtual void mouse_action(int x, int y,int what)=0;
};


#endif	//_UVWIDGET_H_
