#include "uv_gui.h"


int main(int argc, char *argv[])
{
	uv_window test(800,600);
	uv_window sef(500,500,&test);
	run();
	
   return 0;
};
