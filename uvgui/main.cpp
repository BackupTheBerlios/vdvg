//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
void calli();      //Button1 Action
void calli2();     //Button2 Action
void mainloop();   //Hauptschleife
//---------------------------------------------------------------------------
//Hauptprogramm
int main (int argc, char *argv[])
{
    uv_main::mainwindow.set_callback(mainloop);
    uv_main::Button1.set_callback((voidcallback) calli);
    uv_main::Button2.set_callback((voidcallback) calli2);
    uv_main::test.set_texcoordinaten(0.5, 0, 1, 1);
    uv_main::mainwindow.run();
    return 0;
};
//---------------------------------------------------------------------------
void mainloop()
{
    //momentan noch leer
};
//---------------------------------------------------------------------------
void calli()
{
    uv_main::Button2.set_visible(!uv_main::Button2.get_visible());
};
//---------------------------------------------------------------------------
void calli2()
{
    uv_main::mainwindow.set_run(false);
};
//---------------------------------------------------------------------------
