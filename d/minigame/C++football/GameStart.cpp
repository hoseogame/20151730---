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

	cout << "������ �����ϼ���(1�Ǵ� 2�� �����մϴ�)";
	cout << "\n";
	cout << "1, ǲ������ 2, ������ũ����";
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