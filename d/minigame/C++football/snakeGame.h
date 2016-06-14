#pragma once
#include "gameScene.h"


class SnakeGame : public GameScene
{
private:
	static GameScene* GS;
	bool isGameRun;
public:
	//GameScene�� ��ӹ��� �κ�
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit SnakeGame();
	~SnakeGame();

	static void setScene(GameScene* cur);

};
