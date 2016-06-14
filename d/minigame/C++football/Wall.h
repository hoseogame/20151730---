#pragma once
#include "Object.h"

class Wall : public Object
{
public:
	Wall(int x = 0, int y = 0);
	virtual ~Wall();
};