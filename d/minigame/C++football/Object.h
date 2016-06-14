#pragma once
#include <string>
typedef std::string Shape;

class Object
{
private:
	class Postion
	{
	public:
		int x;
		int y;
	public:
		Postion(int _x, int _y) :
			x(_x),
			y(_y)
		{}

		inline void SetPotion(int _x, int _y)
		{
			x = _x;
			y = _y;
		}

		inline int GetX()
		{
			return x;
		}
		inline int GetY()
		{
			return y;
		}
	};
public:
	enum Type{
		food = 0,
		WALL,
		SNAKE
	};

private:
	Postion pos;
	Shape form;
	Type type;

	public:
	Object(int _x, int _y, Shape _form, Type _type);
	virtual ~Object();

	inline Shape GetShape()
	{
		return form;
	}

	inline void SetPotion(int _x, int _y)
	{
		pos.x = _x;
		pos.y = _y;
	}

	inline int GetX()
	{
		return pos.x;
	}
	inline int GetY()
	{
		return pos.y;
	}
	
	inline Type GetType()
	{
		return type;
	}

};