CC = gcc -Wall -ansi -O2 
FILES = main.cpp uv_mainwindow.cpp uv_group.cpp uv_gui.cpp uv_button.cpp uv_widget.cpp uv_window.cpp uv_image.cpp uv_text.cpp uv_array.cpp uv_fpscounter.cpp uv_box.cpp uv_textbox.cpp uv_config.cpp
LIBS = -lGL -lGLU -lfreetype -lSDL_image `sdl-config --libs` 
INCLUDES = -I/usr/include/freetype2 `sdl-config --cflags`
OBJECTS = main.o uv_array.o uv_box.o uv_button.o uv_fpscounter.o uv_group.o uv_gui.o uv_image.o uv_mainwindow.o uv_text.o uv_textbox.o uv_widget.o uv_window.o uv_config.o
LINKER = g++

all: uvgui

debug: 
	make "CC=$(CC) -g"

uvgui: $(OBJECTS) 
	$(LINKER) -o uvgui $(LIBS) $(OBJECTS)

main.o: main.cpp main.h
	$(CC) $(INCLUDES) -c main.cpp

uv_array.o: uv_array.cpp uv_array.h
	$(CC) $(INCLUDES) -c uv_array.cpp

uv_box.o: uv_box.cpp uv_box.h
	$(CC) $(INCLUDES) -c uv_box.cpp

uv_button.o: uv_button.cpp uv_button.h
	$(CC) $(INCLUDES) -c uv_button.cpp

uv_fpscounter.o: uv_fpscounter.cpp uv_fpscounter.h
	$(CC) $(INCLUDES) -c uv_fpscounter.cpp

uv_group.o: uv_group.cpp uv_group.h
	$(CC) $(INCLUDES) -c uv_group.cpp

uv_gui.o: uv_gui.cpp uv_gui.h
	$(CC) $(INCLUDES) -c uv_gui.cpp

uv_image.o: uv_image.cpp uv_image.h
	$(CC) $(INCLUDES) -c uv_image.cpp

uv_mainwindow.o: uv_mainwindow.cpp uv_mainwindow.h
	$(CC) $(INCLUDES) -c uv_mainwindow.cpp

uv_text.o: uv_text.cpp uv_text.h
	$(CC) $(INCLUDES) -c uv_text.cpp

uv_textbox.o: uv_textbox.cpp uv_textbox.h
	$(CC) $(INCLUDES) -c uv_textbox.cpp

uv_widget.o: uv_widget.cpp uv_widget.h
	$(CC) $(INCLUDES) -c uv_widget.cpp

uv_window.o: uv_window.cpp uv_window.h
	$(CC) $(INCLUDES) -c uv_window.cpp

uv_config.o: uv_config.cpp uv_config.h
	$(CC) $(INCLUDES) -c uv_config.cpp

clean: 
	@echo Cleaning Up...
	@rm uvgui
	@rm $(OBJECTS)
	@echo Done.
