#include "uv_config.h"

uv_config::uv_config()
{

}

uv_config::~uv_config()
{

}

bool uv_config::load_file(char *filename)
{
	set_standard_config();
	char temp[500];
	ifstream file(filename);
	if(file.fail()) return 0;
	while( file.getline(temp,500) )
	{
		string tmp=temp;
		make_string_lowercase(tmp);
		if( tmp.find('#',0) == string::npos ) //kein Kommentar (gefunden ;-)
		{
			string leftside = tmp.substr(0, tmp.find('=',0) );
			string rightside = tmp.substr(tmp.find('=',0)+1 );
			if( leftside == "width" ) akt_config.width = get_int(rightside);
			if( leftside == "height" ) akt_config.height = get_int(rightside);
	    	if( leftside == "fullscreen" ) akt_config.fullscreen = get_bool(rightside);
			if( leftside == "color_depth") akt_config.color_depth = get_int(rightside);
		}
	}
	file.close();
	return 1;
}

bool uv_config::save_file(char *filename)
{
 ofstream file(filename);
 stringstream temp;
 temp.str("");
 temp << "width=" << akt_config.width << endl;
 temp << "height=" << akt_config.height << endl;
 temp << "fullscreen=" << akt_config.fullscreen << endl;
 temp << "color_depth=" << akt_config.color_depth << endl;
 file.write(temp.str().c_str(),temp.str().length());
 file.close();
 return 1;
}


bool uv_config::save_standard_file()
{
return 1;
}

config uv_config::get_config()
{
return akt_config;

}

bool uv_config::set_config(config configuration)
{
akt_config = configuration;
return 1;
}

void uv_config::set_standard_config()
{
		akt_config.width = 800;
		akt_config.height = 600;
		akt_config.fullscreen = 0;
		akt_config.color_depth = 32;
}

int uv_config::get_int(string a)
{
	unsigned int temp=0;
	for (unsigned int i=0; i< a.length(); i++)
	{
		temp = temp*10 + (a[i]-48);
	}
	return temp;
}

bool uv_config::get_bool(string a)
{
if(a == "1" || a == "true" || a=="wahr") return 1;
return 0;
}

void uv_config::make_string_lowercase(string &a)
{
	for(unsigned int i=0; i<a.length();i++)
	{
		if( 64 < a[i] && 91 > a[i]) a[i] = a[i]+32;
	}
}
