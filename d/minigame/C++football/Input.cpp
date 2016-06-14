#include <Windows.h>
#include "Snake.h"
#include <conio.h>
#include "Input.h"

char Input::inkey = NULL;

void Input::KeyInput(Snake* sna)
{
	if (_kbhit())
	{
		inkey = _getch();

		switch (inkey)
		{
		case LEFT:
			sna->SetDirection(Snake::LEFT);
			break;

		case RIGHT:
			sna->SetDirection(Snake::RIGHT);
			break;

		case UP:
			sna->SetDirection(Snake::UP);
			break;

		case DOWN:
			sna->SetDirection(Snake::DOWN);
			break;
		}

	}
}