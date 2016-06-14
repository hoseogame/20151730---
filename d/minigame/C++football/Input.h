#pragma once
class Snake;
class Input
{
private:
	enum keyCode{LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80};

	static char inkey;
	 Input();
	~Input();
public:
	static void KeyInput(Snake* sna);

};