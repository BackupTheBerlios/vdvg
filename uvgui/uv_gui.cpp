//Diese Source Datei beinhaltet einige Zeiger und globale Funktionen...
void run();
void set_root_pointer(uv_window *ptr);


static uv_window *root_pointer;


void set_root_pointer(uv_window *ptr)
{
	root_pointer=ptr;
}

void run()
{
	while(1)
		root_pointer->draw();
	
}
