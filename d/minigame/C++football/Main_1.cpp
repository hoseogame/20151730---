#include <iostream>
#include <Windows.h>
#include "Main_1.h"
#include "snakeGame.h"
#include "End.h"
#include "map.h"

using namespace std;

Main_1::Main_1(int _w, int _h, int _s) : 
GameScene(), gameOver(true), width(_w), high(_h), speed(_s)
{}

void Main_1::Init()
{
	map::GetInstance()->SetWalls(width, high);
	map::GetInstance()->SetSnake();
}
bool Main_1::Update()
{
	while (gameOver)
	{
	map::GetInstance()->Setfoods();
	map::GetInstance()->UpdateSnake();
	Main_1::Render();
	gameOver = map::GetInstance()->CollisionCheck();
	Sleep(speed);
	}

	return true;
}
void Main_1::Render()
{
	map::GetInstance()->RenderObjects();
}
void Main_1::Release()
{
	SnakeGame::setScene(new End(width, high, speed, map::GetInstance()->GetCcore() / 25));
	map::ReleaseInstace();
}