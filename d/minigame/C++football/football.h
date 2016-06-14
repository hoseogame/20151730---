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
		int nIsReady;        // �غ� ����(1), ������(0)
		int nMoveX, nMoveY;  // �̵� ��ǥ
		clock_t MoveTime;    // �̵� �ð� ����
		clock_t OldTime;     // ���� �̵� �ð�
	} BALL;

	typedef struct _GOAL_DAE
	{
		int nMoveX, nMoveY;     // �̵� ��ǥ 
		int nLength;			// ��� ����	
		int nLineX[7];			// ���� ���� x ��ǥ (7��)
		clock_t	MoveTime;		// �̵� �ð� ����
		clock_t	OldTime;	    // ���� �̵� �ð�
		int	nDist;				// �̵� �Ÿ�
	} GOAL_DAE;

	typedef struct _EFFECT
	{
		clock_t StratTime; // ȿ�� �߻� �ð�
		clock_t StayTime;  // ȿ�� ���� �ð�	
	} EFFECT;

	typedef struct _STAGE_INFO
	{
		int nGoalBall;			// �����ؾ� �� ���� ���� 
		clock_t LimitTime;      // ���� �ð� 
		int nGoalDaeLength;		// ��� ���� 
		int nGoalDaeX;			// ��� �̵� X ��ǥ
		int nGoalDaeY;			// ��� �̵� Y ��ǥ 
		clock_t MoveTime;		// ��� �̵� �ð� ����
		int nDist;				// ��� �̵� �Ÿ�
	} STAGE_INFO;
protected:
	char* g_strPlayer;		/* = "�����ܦ���";*/
	STAGE_INFO g_sStageInfo[2]; /*= { { 3, 1000 * 20, 1, 20, 3, 300, 1 }, { 10, 1000 * 30, 2, 20, 5, 300, 1 } };*/

	int g_nLength, g_nGoal, g_nBallCount, g_nGoalBallCount, g_nIsGoal, g_nStage; // g_nStage �ʱ�ȭ��
	clock_t g_LimitTime, g_GameStartTime, g_UpdateOldTime;

	GAME_STATE g_GameState = INIT;
public:
	GOAL_DAE g_sGoalDae;
	BALL g_sBall;
	PLAYER g_sPlayer;
	EFFECT g_sEffect;
};

#endif