CC = gcc -Wall -ansi
FILES = main.cpp uv_mainwindow.cpp uv_group.cpp uv_gui.cpp uv_button.cpp uv_widget.cpp uv_window.cpp uv_texture.cpp uv_imagebox.cpp
LIBS = -O2 -lGL -lGLU -lSDL_image `sdl-config --cflags --libs` -I/usr/include/SDL/

all:
	$(CC) $(FILES) $(LIBS) -o uvgui 

debug:
	$(CC) $(FILES) $(LIBS) -g  -o uvgui
 
clean: 
	@echo Cleaning Up...
	@rm uvgui
	@echo Done.
