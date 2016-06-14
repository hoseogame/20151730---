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
		//SoundInit(); // ���� �ʱ�ȭ
		g_nStage = 0;
		//FMOD_CHANNEL_FREE( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // �Ұ� ����� ��ü���� �ѹ��� �����Ѵ�.
	}

	g_LimitTime = g_sStageInfo[g_nStage].LimitTime;  // ���� �ð� ����
	g_nGoalBallCount = g_sStageInfo[g_nStage].nGoalBall; // ��ǥ ���� ����

	g_sPlayer.nCenterX = 4;
	g_sPlayer.nCenterY = 0;
	g_sPlayer.nMoveX = 20;
	g_sPlayer.nMoveY = 22;
	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
	g_nLength = strlen(g_strPlayer);

	// ���� �ʱ�ȭ
	g_sBall.nIsReady = 1;
	g_sBall.nMoveX = g_sPlayer.nMoveX;
	g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
	g_sBall.MoveTime = 100;

	// ��� �ʱ�ȭ
	g_sGoalDae.nMoveX = g_sStageInfo[g_nStage].nGoalDaeX;
	g_sGoalDae.nMoveY = g_sStageInfo[g_nStage].nGoalDaeY;
	g_sGoalDae.nLength = g_sStageInfo[g_nStage].nGoalDaeLength;
	g_sGoalDae.MoveTime = g_sStageInfo[g_nStage].MoveTime;
	g_sGoalDae.OldTime = clock();
	g_sGoalDae.nDist = g_sStageInfo[g_nStage].nDist;
	nLength = g_sGoalDae.nLength * 2 + 1; // Note: �迭�� �ִ� ����

	for (i = 0; i < nLength; i++)
	{
		g_sGoalDae.nLineX[i] = g_sGoalDae.nMoveX + 2 * (i + 1);
	}

	// ȿ�� 
	g_sEffect.StayTime = 2000; // 2�� ����
	g_nGoal = 0;      // �������� �Ϸ� ����
	g_UpdateOldTime = clock();
	g_nBallCount = 0;  // ������ ���� ����
}

void f_function::Update()
{
	{
		clock_t CurTime = clock();
		int nLength = g_sGoalDae.nLength * 2 + 1; // Note: �迭�� �ִ� ����
		int i;


		switch (g_GameState)
		{
		case READY:
			if (CurTime - g_UpdateOldTime > 2000)  // 2��
			{
				g_GameState = RUNNING;
				g_GameStartTime = CurTime;

				//FMOD_Channel_Stop( g_Channel[3] );  // ready ���� ����
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running �����
			}
			break;
		case RUNNING:
			if (CurTime - g_GameStartTime > g_LimitTime) // Note: ���� �ð�
			{
				g_GameState = STOP;
				return;
			}
			else{
				// Note: ���
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
						g_sGoalDae.nDist = g_sGoalDae.nDist * -1; // -1 �� ������ �ٲپ� ��.
					}
				}

				if (g_sBall.nIsReady == 0) // �̵� ���� �� 
				{	// �̵� �ð� ���ݿ� ���� �̵�
					if ((CurTime - g_sBall.OldTime) > g_sBall.MoveTime)
					{
						if (g_sBall.nMoveY - 1 > 0)
						{
							g_sBall.nMoveY--;
							g_sBall.OldTime = CurTime; // ���� �̵� �ð��� ���ϱ� ���� ���� �ð��� ���� �ð� ������ ����

							// ��� ���� �浹
							if (g_sBall.nMoveX >= g_sGoalDae.nLineX[0] && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 1)
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // �� �ʱ�ȭ
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
									g_nBallCount++;  // ������ ���� ����										

									if (g_nBallCount == g_nGoalBallCount) // ���� ��ǥ ������ ������ ������ SUCCESS
									{
										g_GameState = STOP;
										g_nGoal = 1;
										return;
									}

									// ȿ�� ���
									if (g_nIsGoal == 0)
									{
										g_nIsGoal = 1;
										g_sEffect.StratTime = CurTime;
									}

									// ���� ���� ���
									//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // ���� ���� �Ϳ�~
								}
								// ��� �浹 
							}
							else if ((g_sBall.nMoveX >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[nLength - 1] + 3) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 3))
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // �� �ʱ�ȭ
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
								}
							}
						}
						else{ // �� �ʱ�ȭ
							g_sBall.nIsReady = 1;
							g_sBall.nMoveX = g_sPlayer.nMoveX;
							g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
						}
					}
				}
				else{
					g_sBall.nMoveX = g_sPlayer.nMoveX;
				}

				// ȿ�� 
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
				//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
				//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����

				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // �̼� ���� ����
			}
			else{
				g_GameState = FAILED;
				//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // �̼� ���� ����
			}
			break;
		case SUCCESS:
			if (CurTime - g_UpdateOldTime > 3000)
			{
				g_UpdateOldTime = CurTime;
				++g_nStage;
				Init();
				g_GameState = READY;
				//FMOD_Channel_Stop( g_Channel[4] );  // �̼� ���� ���� ��� ����					
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY ���� 
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
		screen.ScreenPrint(g_sGoalDae.nMoveX, g_sGoalDae.nMoveY, "��");
		nLength = g_sGoalDae.nLength * 2 + 1;

		for (i = 0; i < nLength; i++)
			screen.ScreenPrint(g_sGoalDae.nLineX[i], g_sGoalDae.nMoveY, "��");

		screen.ScreenPrint(g_sGoalDae.nLineX[nLength - 1] + 2, g_sGoalDae.nMoveY, "��");

		// Note: ȿ�� ���  	
		if (g_nIsGoal == 1)
		{
			screen.GoalMessage(10, 10);
		}

		// Note: 2 �÷��� Ŭ���� 
		if (g_sPlayer.nX < 2)  //  ���� Ŭ���� ó��
			screen.ScreenPrint(2, g_sPlayer.nMoveY, &g_strPlayer[(g_sPlayer.nX - 2)*-1]);	 // ��ǥ�� �迭 �ε��� 
		else if (g_sPlayer.nMoveX + (g_nLength - g_sPlayer.nCenterX + 1) > 43) // ������ Ŭ���� ó��
		{
			strncat(string, g_strPlayer, g_nLength - ((g_sPlayer.nMoveX + g_sPlayer.nCenterX + 1) - 43));
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, string);
		}
		else{ // 1 �÷��� �̵�
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, g_strPlayer);
		}

		screen.ScreenPrint(g_sBall.nMoveX, g_sBall.nMoveY, "��");
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

	// Note: ������ �� 
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
				if (g_sPlayer.nMoveX > 2) // ���� �浹 ��� ��ǥ üũ
				{
					g_sPlayer.nMoveX--;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
					// Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� ) 
					if (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2 || g_sPlayer.nMoveX + nRemain > 43)
						g_sPlayer.nMoveX--;

					g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
				}
				break;
			case 'l':
				if (g_sPlayer.nMoveX + 1 < 43) // ������ �浹 ��� ��ǥ üũ
				{
					g_sPlayer.nMoveX++;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
					// Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� )
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
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // �� ���� �Ҹ� ���
				}
				break;

			case 'y':
			case 'Y':
				if (g_GameState == FAILED)
				{
					Init();
					g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ���� 
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
				}
				break;
			case 'n':
			case 'N':
				if (g_GameState == FAILED)
				{
					g_GameState = RESULT;
					//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ����							
				}
				break;

			case ' ':
				if (g_GameState == INIT && g_nStage == 0)
				{
					g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready ����
					g_UpdateOldTime = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
				}
				break;
			}
		}

		Update();    // ������ ����
		Render();    // ȭ�� ���
		//FMOD_System_Update( g_System );		
	}

	Release();   // ����
	/*ScreenRelease();*/
	screen.ScreenRelease();
}