//---------------------------------------------------------------------------
// File:       uv_fpscounter.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny Löffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sat Oct-02-2004 17:05:42 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_FPSCOUNTER_H_
#define _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
#include "uv_include.h"
#include "SDL.h"

#include <string>
#include <iostream>
#include <sstream>  //für stringstream
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class uv_fpscounter:public uv_group
{
   private:
      uv_text counter;
      std::string IntToString(const int & value);

   public:
      uv_fpscounter(uv_group *parent);
      void draw(basic_string<GLuint> * clist);
};
//---------------------------------------------------------------------------
#endif // _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
