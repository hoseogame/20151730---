#include <iostream>
#include "Object.h"

using namespace std;

Object::Object(int _x, int _y, Shape _form, Type _type) : pos(_x, _y), form(_form), type(_type)
{}

Object::~Object() {}