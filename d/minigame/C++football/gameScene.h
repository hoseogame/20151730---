#pragma once

class GameScene
{
private:
	GameScene(const GameScene& GS);
	GameScene& operator=(const GameScene& GS);

public:
	explicit GameScene();
	virtual ~GameScene();

	virtual void Init() = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};