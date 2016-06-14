#pragma once
#include "gameScene.h"

class Intro : public GameScene
{
private:
	int width, high;
	int speed;
public:
	//GameScene�� ��ӹ��� �κ�
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Intro();

};