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
	void InitScreen();		// 초기화면
	void ReadyScreen(int* g_nStage);		//	몇 스테이지 화면
	void BackScreen(int* g_nStage, STAGE_INFO *g_sStageInfo, clock_t *g_GameStartTime);
	void GoalMessage(int nX, int nY);	// 골인
	void SuccessScreen();	// 미션 성공
	void FailureScreen();	// 미션 실패
	void ResultScreen(int* g_nStage);	// 성공한 스테이지가 몇 인가
};


#endif