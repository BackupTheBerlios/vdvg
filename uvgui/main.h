//---------------------------------------------------------------------------
#ifndef Main.h
#define Main.h
//---------------------------------------------------------------------------
namespace uv_main
{
   uv_mainwindow mainwindow(1024, 768, false, "test");

   uv_imagebox img(0,0,1024,768,&mainwindow,"background.jpg");
   uv_window window1(50,50,600,300,&mainwindow,"auh");
   uv_window window2(400,450,300,200,&mainwindow,"jkh");
   //uv_window window3(800, 200, 100, 200, &mainwindow, "test");
   //uv_window window2(30,100,200,150,&window1,"jkh");
   //uv_button Button1(30,30,256,64,&window1);
   uv_button Button2(30,30,256,64,&window2);
   uv_text Text1(10, 30, 30, 20, &window1, "hello uv_world!");
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
