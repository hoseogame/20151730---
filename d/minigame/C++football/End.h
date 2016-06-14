#pragma once
#include "gameScene.h"


class End : public GameScene
{
private:
	int width, high;
	int speed;
	int score;

public:
	//GameScene�� ��ӹ��� �κ�
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit End(int _w, int _h, int _speed, int _socre);
};