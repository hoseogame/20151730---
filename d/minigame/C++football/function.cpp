#include"function.h"

f_function::f_function()
{
	Init();
	input();
}

void f_function::Init()
{
	int nLength, i;

	if (g_nStage == -1)
	{
		//SoundInit(); // 사운드 초기화
		g_nStage = 0;
		//FMOD_CHANNEL_FREE( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // 소개 사운드는 전체에서 한번만 실행한다.
	}

	g_LimitTime = g_sStageInfo[g_nStage].LimitTime;  // 제한 시간 설정
	g_nGoalBallCount = g_sStageInfo[g_nStage].nGoalBall; // 목표 골인 개수

	g_sPlayer.nCenterX = 4;
	g_sPlayer.nCenterY = 0;
	g_sPlayer.nMoveX = 20;
	g_sPlayer.nMoveY = 22;
	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
	g_nLength = strlen(g_strPlayer);

	// 공의 초기화
	g_sBall.nIsReady = 1;
	g_sBall.nMoveX = g_sPlayer.nMoveX;
	g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
	g_sBall.MoveTime = 100;

	// 골대 초기화
	g_sGoalDae.nMoveX = g_sStageInfo[g_nStage].nGoalDaeX;
	g_sGoalDae.nMoveY = g_sStageInfo[g_nStage].nGoalDaeY;
	g_sGoalDae.nLength = g_sStageInfo[g_nStage].nGoalDaeLength;
	g_sGoalDae.MoveTime = g_sStageInfo[g_nStage].MoveTime;
	g_sGoalDae.OldTime = clock();
	g_sGoalDae.nDist = g_sStageInfo[g_nStage].nDist;
	nLength = g_sGoalDae.nLength * 2 + 1; // Note: 배열의 최대 길이

	for (i = 0; i < nLength; i++)
	{
		g_sGoalDae.nLineX[i] = g_sGoalDae.nMoveX + 2 * (i + 1);
	}

	// 효과 
	g_sEffect.StayTime = 2000; // 2초 설정
	g_nGoal = 0;      // 스테이지 완료 변수
	g_UpdateOldTime = clock();
	g_nBallCount = 0;  // 골인한 공의 개수
}

void f_function::Update()
{
	{
		clock_t CurTime = clock();
		int nLength = g_sGoalDae.nLength * 2 + 1; // Note: 배열의 최대 길이
		int i;


		switch (g_GameState)
		{
		case READY:
			if (CurTime - g_UpdateOldTime > 2000)  // 2초
			{
				g_GameState = RUNNING;
				g_GameStartTime = CurTime;

				//FMOD_Channel_Stop( g_Channel[3] );  // ready 사운드 중지
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running 배경음
			}
			break;
		case RUNNING:
			if (CurTime - g_GameStartTime > g_LimitTime) // Note: 제한 시간
			{
				g_GameState = STOP;
				return;
			}
			else{
				// Note: 골대
				if (CurTime - g_sGoalDae.OldTime > g_sGoalDae.MoveTime)
				{
					g_sGoalDae.OldTime = CurTime;
					if (g_sGoalDae.nMoveX + g_sGoalDae.nDist >= 2 && ((g_sGoalDae.nLineX[nLength - 1] + 3) + g_sGoalDae.nDist) <= 43)
					{
						g_sGoalDae.nMoveX += g_sGoalDae.nDist;
						for (i = 0; i < nLength; i++)
						{
							g_sGoalDae.nLineX[i] = g_sGoalDae.nMoveX + 2 * (i + 1);
						}
					}
					else{
						g_sGoalDae.nDist = g_sGoalDae.nDist * -1; // -1 이 방향을 바꾸어 줌.
					}
				}

				if (g_sBall.nIsReady == 0) // 이동 중일 때 
				{	// 이동 시간 간격에 의한 이동
					if ((CurTime - g_sBall.OldTime) > g_sBall.MoveTime)
					{
						if (g_sBall.nMoveY - 1 > 0)
						{
							g_sBall.nMoveY--;
							g_sBall.OldTime = CurTime; // 다음 이동 시각과 비교하기 위해 현재 시간을 이전 시간 변수에 저장

							// 골대 라인 충돌
							if (g_sBall.nMoveX >= g_sGoalDae.nLineX[0] && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 1)
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // 공 초기화
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
									g_nBallCount++;  // 골인한 공의 개수										

									if (g_nBallCount == g_nGoalBallCount) // 공과 목표 공과의 개수가 같으면 SUCCESS
									{
										g_GameState = STOP;
										g_nGoal = 1;
										return;
									}

									// 효과 출력
									if (g_nIsGoal == 0)
									{
										g_nIsGoal = 1;
										g_sEffect.StratTime = CurTime;
									}

									// 골인 사운드 출력
									//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 골인 사운드 와우~
								}
								// 골대 충돌 
							}
							else if ((g_sBall.nMoveX >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[nLength - 1] + 3) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 3))
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // 공 초기화
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
								}
							}
						}
						else{ // 공 초기화
							g_sBall.nIsReady = 1;
							g_sBall.nMoveX = g_sPlayer.nMoveX;
							g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
						}
					}
				}
				else{
					g_sBall.nMoveX = g_sPlayer.nMoveX;
				}

				// 효과 
				if (g_nIsGoal == 1)
				{
					if (CurTime - g_sEffect.StratTime > g_sEffect.StayTime)
						g_nIsGoal = 0;
				}
			}
			break;
		case STOP:
			if (g_nGoal == 1)
			{
				g_GameState = SUCCESS;
				g_UpdateOldTime = CurTime;
				//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지
				//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지

				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // 미션 성공 사운드
			}
			else{
				g_GameState = FAILED;
				//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // 미션 실패 사운드
			}
			break;
		case SUCCESS:
			if (CurTime - g_UpdateOldTime > 3000)
			{
				g_UpdateOldTime = CurTime;
				++g_nStage;
				Init();
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[4] );  // 미션 성공 사운드 출력 중지					
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY 사운드 
			}
			break;
		}
	}
}

void f_function::Render()
{
	char string[100] = { 0, };
	int nLength, i;

	screen.ScreenClear();

	switch (g_GameState)
	{
	case INIT:
		if (g_nStage == 0)
			screen.InitScreen();
		break;
	case READY:
		screen.ReadyScreen(&g_nStage);
		break;
	case RUNNING:
		screen.BackScreen(&g_nStage, g_sStageInfo, &g_GameStartTime);
		screen.ScreenPrint(g_sGoalDae.nMoveX, g_sGoalDae.nMoveY, "□");
		nLength = g_sGoalDae.nLength * 2 + 1;

		for (i = 0; i < nLength; i++)
			screen.ScreenPrint(g_sGoalDae.nLineX[i], g_sGoalDae.nMoveY, "━");

		screen.ScreenPrint(g_sGoalDae.nLineX[nLength - 1] + 2, g_sGoalDae.nMoveY, "□");

		// Note: 효과 출력  	
		if (g_nIsGoal == 1)
		{
			screen.GoalMessage(10, 10);
		}

		// Note: 2 컬럼씩 클리핑 
		if (g_sPlayer.nX < 2)  //  왼쪽 클리핑 처리
			screen.ScreenPrint(2, g_sPlayer.nMoveY, &g_strPlayer[(g_sPlayer.nX - 2)*-1]);	 // 좌표를 배열 인덱스 
		else if (g_sPlayer.nMoveX + (g_nLength - g_sPlayer.nCenterX + 1) > 43) // 오른쪽 클리핑 처리
		{
			strncat(string, g_strPlayer, g_nLength - ((g_sPlayer.nMoveX + g_sPlayer.nCenterX + 1) - 43));
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, string);
		}
		else{ // 1 컬럼씩 이동
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, g_strPlayer);
		}

		screen.ScreenPrint(g_sBall.nMoveX, g_sBall.nMoveY, "⊙");
		break;
	case SUCCESS:
		screen.SuccessScreen();
		break;
	case FAILED:
		screen.FailureScreen();
		break;
	case RESULT:
		screen.ResultScreen(&g_nStage);
		break;
	}

	// Note: 렌더링 끝 
	screen.ScreenFlipping();
}
void f_function::Release()
{
	int i;
	/*for( i = 0 ; i < 7 ; i++ )
	FMOD_Sound_Release( g_Sound[i] );

	FMOD_System_Close( g_System );
	FMOD_System_Release( g_System ); */
}

void f_function::input()
{
	while (1)
	{
		if (_kbhit())
		{
			if (g_GameState == RESULT)
				break;

			nKey = _getch();

			switch (nKey)
			{
			case 'j':
				if (g_sPlayer.nMoveX > 2) // 왼쪽 충돌 경계 좌표 체크
				{
					g_sPlayer.nMoveX--;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1; // 전체 길이 - ( 중심 좌표 + 1 )은 남은 길이
					// Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 ) 
					if (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2 || g_sPlayer.nMoveX + nRemain > 43)
						g_sPlayer.nMoveX--;

					g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
				}
				break;
			case 'l':
				if (g_sPlayer.nMoveX + 1 < 43) // 오른쪽 충돌 경계 좌표 체크
				{
					g_sPlayer.nMoveX++;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1; // 전체 길이 - ( 중심 좌표 + 1 )은 남은 길이
					// Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 )
					if (g_sPlayer.nMoveX + nRemain > 43 || (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2))
						g_sPlayer.nMoveX++;

					g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
				}
				break;
			case 'k':
				if (g_sBall.nIsReady && g_GameState == RUNNING)
				{
					g_sBall.nMoveX = g_sPlayer.nMoveX;
					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
					g_sBall.OldTime = clock();
					g_sBall.nIsReady = 0;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 슛 동작 소리 출력
				}
				break;

			case 'y':
			case 'Y':
				if (g_GameState == FAILED)
				{
					Init();
					g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지 
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
				}
				break;
			case 'n':
			case 'N':
				if (g_GameState == FAILED)
				{
					g_GameState = RESULT;
					//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지							
				}
				break;

			case ' ':
				if (g_GameState == INIT && g_nStage == 0)
				{
					g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[0] ); // 배경음 중지
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready 사운드
					g_UpdateOldTime = clock();  // ready를 일정시간 지속해 주기 위해 							
				}
				break;
			}
		}

		Update();    // 데이터 갱신
		Render();    // 화면 출력
		//FMOD_System_Update( g_System );		
	}

	Release();   // 해제
	/*ScreenRelease();*/
	screen.ScreenRelease();
}