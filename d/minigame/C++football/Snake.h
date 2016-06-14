#pragma once
#include "Object.h"

using namespace std;

class Snake
{
public:
	class SnakeBody : public Object
	{
	public:
		SnakeBody(int x = 0, int y = 0) : Object(x, y, "бр", Type::SNAKE)
		{};
		virtual ~SnakeBody(){};
	};

	enum Direction{
		LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, STOP = 100
	};

private:
	Snake(const Snake&);
	Snake& operator=(const Snake&);

private:
	SnakeBody* sBody;
	Direction dir;
	int size;
public:
	explicit Snake(int width, int high);
	virtual ~Snake();

	void UpdateTail();
	void AddTail();

	inline SnakeBody* GetBodys()
	{	
		return sBody;
	}
	inline void SetDirection(Direction _dir)
	{
		dir = _dir;
	}
	inline int GetSize()
	{
		return size;
	}
};