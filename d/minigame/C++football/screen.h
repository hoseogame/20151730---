#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_
#include"football.h"

class f_screen:public football 
{
protected:
	static int g_nScreenIndex;
	static HANDLE g_hScreen[2];
public:
	f_screen();

	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint(int x, int y, char *string);
	void SetColor(unsigned short color);
public:
	void InitScreen();		// �ʱ�ȭ��
	void ReadyScreen(int* g_nStage);		//	�� �������� ȭ��
	void BackScreen(int* g_nStage, STAGE_INFO *g_sStageInfo, clock_t *g_GameStartTime);
	void GoalMessage(int nX, int nY);	// ����
	void SuccessScreen();	// �̼� ����
	void FailureScreen();	// �̼� ����
	void ResultScreen(int* g_nStage);	// ������ ���������� �� �ΰ�
};


#endif