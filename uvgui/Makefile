CC = gcc -Wall -ansi

all:
	$(CC) main.cpp uv_window.cpp uv_gui.cpp -o uvgui -lGL -lGLU `sdl-config --cflags --libs`

clean: 
	@echo Cleaning Up...
	@rm uvgui
	@echo Done.
