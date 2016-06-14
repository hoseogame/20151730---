#pragma once
#ifndef _function_H_
#define  _function_H_

#include"football.h"
#include"screen.h"

class f_function:public football
{
public:
	f_function();

	void Init();
	void Update();
	void Render();
	void Release();
	void input();
public:
	f_screen screen;
	football Football;
};

#endif