//---------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
//---------------------------------------------------------------------------
namespace uv_main
{
uv_mainwindow mainwindow(1024, 768, 1, "4D4G");

uv_image img(0,0,1024,768,&mainwindow,"background.jpg");
uv_window window1(50,50,600,300,&mainwindow,"auh");
uv_image test(20, 110, 64, 64, &window1,"test3.tga");
//uv_image test("test3.tga");
uv_fpscounter fps(&mainwindow);
uv_window window2(400,450,300,200,&mainwindow,"jkh");
//uv_window window3(800, 200, 100, 200, &mainwindow, "test");
//uv_window window2(30,100,200,150,&window1,"jkh");
//uv_text testtext(400, 300, 200, 30, &mainwindow, "test");
uv_button Button1(30,30,256,64,&window1,"Klick Mich !");
uv_button Button2(30,30,256,64,&window2,"Beenden");

//Dies ist Lukis Kommentar

};
//---------------------------------------------------------------------------
#endif
