/*
-----------------------------------------------------------------------------
4D 4Gewinnt is simple board game.
Copyright (C) 2004 Benny Loeffel, Lukas Humbel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
-----------------------------------------------------------------------------
*/
//Klass zum Verwalten einiger Optionen (Auflösung, etc)
#ifndef _UV_CONFIG_
#define _UV_CONFIG_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "uv_mainwindow.h" //wegen attribute
using namespace std;

struct config
{
   bool fullscreen;
   int width;
   int height;
   int color_depth;
   string caption;
};

class uv_config
{
   private:
      void set_standard_config();
      config akt_config;
      bool file_open;
      string filename;
      int get_int(string a);
      bool get_bool(string a);
      string get_string(string a);
      void make_string_lowercase(string &a);
   public:
      uv_config();
      ~uv_config();
      bool load_file(char *filename);
      bool load_standard_file();
      bool save_file(char *filename);
      bool save_standard_file();
      config get_config();
      bool set_config(config configuration);
	  bool set_fullscreen(bool fs);
      uv_mainwindow::attribute get_mainwindow_attribute();
};

#endif
