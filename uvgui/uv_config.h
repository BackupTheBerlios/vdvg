//Klass zum Verwalten einiger Optionen (Auflösung, etc)
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct config
{
	bool fullscreen;
	int width;
	int height;
	int color_depth;
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
};
