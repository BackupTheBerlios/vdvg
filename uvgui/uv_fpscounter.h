//---------------------------------------------------------------------------
// File:       uv_fpscounter.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Sep-11-2004 21:22:18 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_FPSCOUNTER_H_
#define _UV_FPSCOUNTER_H_

//#include "uv_widget.h"
//#include "uv_group.h"
//#include "uv_text.h"
#include "uv_include.h"
#include "SDL.h"
#include <string>
#include <iostream>
using namespace std;

class uv_fpscounter:public uv_group
{
	private:
	uv_text counter;
	
	public:
	uv_fpscounter(uv_group *parent);
	void draw();
	
};

#endif
