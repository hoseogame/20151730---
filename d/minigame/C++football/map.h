#pragma once
class Object;
class Snake;

class map
{
private:
	explicit map();
	~map();
	map(const map&);
	map& operator=(const map&);

private:
	static map* instnace; 
	Object* Walls;
	Object* Heart;
	Snake* snake;
	int width, hight;
	int wallsCount;
	int score;
	bool isWallsDraw;
	bool isHaertDraw;
	bool isMenuDraw;

public:
	static map* GetInstance();
	static void ReleaseInstace();

	bool CollisionCheck();
	bool CompareRect(int x1, int x2, int y1, int y2);
	void SetWalls(int width, int hight);
	void Setfoods();
	void SetSnake();
	void UpdateSnake();
	void RenderObjects();
	inline int GetCcore()
	{
		return score;
	}
};