#include "uv_gui.h"


int main(int argc, char *argv[])
{
	uv_window test(800,600);
	uv_window sef(200,100,20,20,&test);
	uv_window ssef(200,300,200,400,&test);
	run();
	
   return 0;
};
