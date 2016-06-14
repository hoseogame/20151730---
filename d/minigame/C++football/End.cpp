#include "End.h"
#include <iostream>
#include <Windows.h>

using namespace std;

End::End(int _w, int _h, int _speed, int _socre) : 
width(_w), high(_h), speed(_speed), score(_socre)
{}

void End::Init()
{
	system("cls");
}
bool End::Update()
{
	cout << "가로 세로 : " << width << " " << high << endl;
	cout << "속도 : " << speed << endl;
	cout << "점수 : " << score << endl;
	Sleep(3000);
	Render();
	return false;
}
void End::Render()
{
	system("cls");
}
void End::Release()
{
}