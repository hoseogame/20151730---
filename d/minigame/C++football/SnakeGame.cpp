#include "snakeGame.h"
#include "Intro.h"

GameScene* SnakeGame::GS;

SnakeGame::SnakeGame() : GameScene(), isGameRun(true)
{}

SnakeGame::~SnakeGame()
{}

void SnakeGame::Init()
{
	setScene(nullptr);
}

bool SnakeGame::Update()
{
	if (!GS)
		return false;

	while (isGameRun)
	{
		GS->Init();
		isGameRun = GS->Update();
		GS->Release();
	}
	
	return true;
}
void SnakeGame::Render()
{ }

void SnakeGame::Release()
{
	delete GS;
}

void SnakeGame::setScene(GameScene* cur)
{
	if (GS == nullptr)
		GS = new Intro();
	else if (cur != nullptr)
	{
		delete GS;
		GS = cur;
	}
}
