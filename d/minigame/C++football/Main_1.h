#pragma once
#include "gameScene.h"


class Main_1 : public GameScene
{
private:
	bool gameOver;
	int width, high;
	int speed;
public:
	//GameScene로 상속받은 부분
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Main_1(int _w, int _h, int _s);
};
