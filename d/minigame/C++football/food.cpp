#include <iostream>
#include <string>
#include "gotoxy.h"
#include "food.h"

using namespace std;

food::food(int _x, int _y) : Object(_x, _y, "��", Type::food)
{
}

food:: ~food()
{
}