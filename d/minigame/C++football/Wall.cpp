#include <iostream>
#include <string>

#include "Wall.h"

using namespace std;

Wall::Wall(int _x, int _y) : Object(_x, _y, "��", Type::WALL)
{}

Wall::~Wall(){}