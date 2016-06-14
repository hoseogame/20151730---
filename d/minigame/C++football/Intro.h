#pragma once
#include "gameScene.h"

class Intro : public GameScene
{
private:
	int width, high;
	int speed;
public:
	//GameScene로 상속받은 부분
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Intro();

};