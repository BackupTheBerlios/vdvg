#include "uv_gui.h"
#include "uv_mainwindow.h"
#include "uv_button.h"
#include "uv_window.h"

using namespace std;

void calli();

uv_button *rpr;

int main (int argc, char *argv[])
{
    uv_mainwindow fenster(1024,768,1,"test");
    uv_window fens2(50,50,200,200,&fenster,"auh");
    uv_button knopf(10,10,50,50,&fens2 );
    uv_button knopf2(70,70,50,50,&fens2 );
    knopf2.set_visible(1);
    rpr=&knopf2;
    knopf.set_callback((voidcallback) calli);
    fenster.run();
    return 0;
};


void calli()
{
    rpr->set_visible(!rpr->get_visible());
    //cout << "Callback\n";
    /*static int x=10;
    x += 60;
    uv_button *tmp = new uv_button(x,10,50,50,rpr);
    tmp->set_callback((voidcallback)calli);
    //cout << "callback"<<endl;*/
}
