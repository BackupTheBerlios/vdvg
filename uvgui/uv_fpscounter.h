#ifndef _UV_FPSCOUNTER_H_
#define _UV_FPSCOUNTER_H_

#include "uv_widget.h"
#include "uv_group.h"
#include "uv_text.h"
#include "SDL.h"
#include <string>
#include <iostream>
using namespace std;

class uv_fpscounter:public uv_widget
{
	private:
	uv_text counter;
	public:
	uv_fpscounter(uv_group *parent);
	void draw();
	
};

#endif
