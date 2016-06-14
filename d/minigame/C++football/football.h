#include<iostream>
#pragma once
#ifndef _FOOTBALL_H_
#define _FOOTBALL_H_

#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
//#include <fmod.h>
//#include "Screen.h"

class football
{
public:
	football();
protected:
	int nKey, nRemain;
protected:
	typedef enum _GAME_STATE
	{
		INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT
	} GAME_STATE;
protected:
	typedef struct _PLAYER
	{
		int nCenterX, nCenterY;
		int nMoveX, nMoveY;
		int nX, nY;
	} PLAYER;

	typedef struct _BALL
	{
		int nIsReady;        // 준비 상태(1), 슛상태(0)
		int nMoveX, nMoveY;  // 이동 좌표
		clock_t MoveTime;    // 이동 시간 간격
		clock_t OldTime;     // 이전 이동 시각
	} BALL;

	typedef struct _GOAL_DAE
	{
		int nMoveX, nMoveY;     // 이동 좌표 
		int nLength;			// 골대 길이	
		int nLineX[7];			// 골인 라인 x 좌표 (7개)
		clock_t	MoveTime;		// 이동 시간 간격
		clock_t	OldTime;	    // 이전 이동 시간
		int	nDist;				// 이동 거리
	} GOAL_DAE;

	typedef struct _EFFECT
	{
		clock_t StratTime; // 효과 발생 시각
		clock_t StayTime;  // 효과 지속 시간	
	} EFFECT;

	typedef struct _STAGE_INFO
	{
		int nGoalBall;			// 골인해야 할 볼의 개수 
		clock_t LimitTime;      // 제한 시간 
		int nGoalDaeLength;		// 골대 길이 
		int nGoalDaeX;			// 골대 이동 X 좌표
		int nGoalDaeY;			// 골대 이동 Y 좌표 
		clock_t MoveTime;		// 골대 이동 시간 간격
		int nDist;				// 골대 이동 거리
	} STAGE_INFO;
protected:
	char* g_strPlayer;		/* = "┗━●━┛";*/
	STAGE_INFO g_sStageInfo[2]; /*= { { 3, 1000 * 20, 1, 20, 3, 300, 1 }, { 10, 1000 * 30, 2, 20, 5, 300, 1 } };*/

	int g_nLength, g_nGoal, g_nBallCount, g_nGoalBallCount, g_nIsGoal, g_nStage; // g_nStage 초기화함
	clock_t g_LimitTime, g_GameStartTime, g_UpdateOldTime;

	GAME_STATE g_GameState = INIT;
public:
	GOAL_DAE g_sGoalDae;
	BALL g_sBall;
	PLAYER g_sPlayer;
	EFFECT g_sEffect;
};

#endif