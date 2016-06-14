#include <iostream>
#include "football.h"
#include "function.h"
#include "screen.h"
#include "snakeGame.h"
#include "gotoxy.h"

using namespace std;


void main()
{
	int choice;

	cout << "게임을 선택하세여(1또는 2만 가능합니다)";
	cout << "\n";
	cout << "1, 풋볼게임 2, 스네이크게임";
	cout << "\n";
	cin >> choice;

	if (choice == 1)
	{
		f_function football_game;
	}
	else if (choice == 2)
	{
		SnakeGame EX;
		EX.Init();
		EX.Update();
		EX.Release();

	}
	else
		exit(0);
}