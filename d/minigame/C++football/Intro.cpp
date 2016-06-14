#include <iostream>
#include "Intro.h"
#include "snakeGame.h"
#include "Main_1.h"
#include <Windows.h>

using namespace std;

Intro::Intro() : width(30), high(30), speed(5)
{}

void Intro::Init()
{}	

bool Intro::Update()
{
	Render();
	return true;
}
void Intro::Render()
{
	system("cls");
	Sleep(1000);
}
void Intro::Release()
{
	system("cls");
	SnakeGame::setScene(new Main_1(width, high, speed * 25));
}