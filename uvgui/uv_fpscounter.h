//---------------------------------------------------------------------------
// File:       uv_fpscounter.h
// Created by: Lukas Hubmel <luki@humbels.com>, Benny L�ffel <benny@ggs.ch>
// Created on: 2004
// Version:    1.0 <last modification: Sun Sep-12-2004 21:35:35 by Benny>
//---------------------------------------------------------------------------
#ifndef _UV_FPSCOUNTER_H_
#define _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
#include "uv_include.h"
#include "SDL.h"

#include <string>
#include <iostream>
#include <sstream>  //f�r stringstream
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
      void draw();
};
//---------------------------------------------------------------------------
#endif // _UV_FPSCOUNTER_H_
//---------------------------------------------------------------------------
