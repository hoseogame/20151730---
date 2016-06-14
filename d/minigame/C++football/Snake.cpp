#include "Snake.h"
#include <iostream>
#include "gotoxy.h"
using namespace std;

Snake::Snake(int width, int high) : dir(RIGHT), size(0)
{
	sBody = new SnakeBody[100];
	sBody[size++].SetPotion(width, high);
}
Snake:: ~Snake()
{}

void Snake::AddTail()
{
	int x = sBody[0].GetX();
	int y = sBody[0].GetY();

	size++;
	for (int i = size - 1; i >= 0; i--)
		sBody[i + 1] = sBody[i];

	switch (dir)
	{
	case Snake::LEFT:
		sBody[0].SetPotion(x - 2, y);
		break;
	case Snake::RIGHT:
		sBody[0].SetPotion(x + 2, y);
		break;
	case Snake::UP:
		sBody[0].SetPotion(x, y - 1);
		break;
	case Snake::DOWN:
		sBody[0].SetPotion(x, y + 1);
		break;
	}
}

void Snake::UpdateTail()
{

	int x = sBody[0].GetX();
	int y = sBody[0].GetY();


	gotoxy(sBody[size - 1].GetX(), sBody[size - 1].GetY());
	cout << "  ";

	for (int i = size - 1; i >= 0; i--)
		sBody[i + 1] = sBody[i];


	switch (dir)
	{
	case Snake::LEFT:
		sBody[0].SetPotion(x - 2, y);
		break;
	case Snake::RIGHT:
		sBody[0].SetPotion(x + 2, y);
		break;
	case Snake::UP:
		sBody[0].SetPotion(x, y - 1);
		break;
	case Snake::DOWN:
		sBody[0].SetPotion(x, y + 1);
		break;

	case Snake::STOP:

		break;
	}
}
