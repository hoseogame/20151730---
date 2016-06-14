#include"screen.h"

int f_screen::g_nScreenIndex = 0;
HANDLE f_screen::g_hScreen[] = { 0 };

f_screen::f_screen()
{
	ScreenInit();
}


void f_screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	// 가상의 콘솔창 2개룰 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void f_screen::ScreenFlipping()
{
	Sleep(10);
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void f_screen::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void f_screen::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}


void f_screen::ScreenPrint(int x, int y, char *string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

// 1 ~ 15 까지 색상 설정 가능
void f_screen::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}

void f_screen::InitScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃             □━━━□                   ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                        ///.   슛~~~      ┃");
	ScreenPrint(0, 5, "┃                       (^.^)              ┃");
	ScreenPrint(0, 6, "┃                      ┗┫ ┣┓           ┃");
	ScreenPrint(0, 7, "┃                         ┏┛             ┃");
	ScreenPrint(0, 8, "┃                     ⊙  ┛＼             ┃");
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃       슛 골인 게임  Go! Go!              ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃       j :왼쪽 l : 오른쪽 k :슛           ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃        ┗●┛  space 키를 눌러주세요     ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void f_screen::ReadyScreen(int* g_nStage)
{
	char string[100];

	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 2, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 3, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 4, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 5, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 6, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 7, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 8, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 9, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 10, "┃■■■■■                    ■■■■■■┃");
	sprintf(string, "┃■■■■■     %d   스테이지   ■■■■■■┃", (*g_nStage + 1));
	ScreenPrint(0, 11, string);
	ScreenPrint(0, 12, "┃■■■■■                    ■■■■■■┃");
	ScreenPrint(0, 13, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 14, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 15, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 16, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 17, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 18, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 19, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 20, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 21, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 22, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void f_screen::BackScreen(int* g_nStage, STAGE_INFO *g_sStageInfo, clock_t *g_GameStartTime)
{
	char string[100];

	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	sprintf(string, "┃                                          ┃스테이지: %d", *g_nStage + 1);
	ScreenPrint(0, 4, string);
	ScreenPrint(0, 5, "┃                                          ┃");
	sprintf(string, "┣━━━━━━━━━━━━━━━━━━━━━┫제한 시간: %d", g_sStageInfo[*g_nStage].LimitTime / 1000);
	ScreenPrint(0, 6, string);
	ScreenPrint(0, 7, "┃                                          ┃");
	sprintf(string, "┃                                          ┃현재 시간: %d", (clock() - *g_GameStartTime) / 1000);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "┃                                          ┃");
	sprintf(string, "┃                                          ┃목표 골인: %d ", g_sStageInfo[*g_nStage].nGoalBall);
	ScreenPrint(0, 10, string);
	ScreenPrint(0, 11, "┃                                          ┃");
	sprintf(string, "┃                                          ┃골인 공 개수: %d ", g_nBallCount);
	ScreenPrint(0, 12, string);

	ScreenPrint(0, 13, "┃                                          ┃");
	sprintf(string, "┃                                          ┃");
	ScreenPrint(0, 14, string);
	ScreenPrint(0, 15, "┃                                          ┃");
	sprintf(string, "┃                                          ┃");
	ScreenPrint(0, 16, string);
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                                          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┃                                          ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void f_screen::GoalMessage(int nX, int nY)
{
	ScreenPrint(nX, nY, "☆ )) 골인 (( ★");
	ScreenPrint(nX, nY + 1, "＼(^^')/ ＼(\"*')/");
	ScreenPrint(nX, nY + 2, "   ■       ■");
	ScreenPrint(nX, nY + 3, "  ┘┐    ┌└");
}

void f_screen::SuccessScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                ////＼＼                  ┃");
	ScreenPrint(0, 7, "┃               q ∧  ∧ p                 ┃");
	ScreenPrint(0, 8, "┃               (└──┘)                 ┃");
	ScreenPrint(0, 9, "┃             ♬ 미션 성공 ♪              ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃                                          ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃                                          ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                                          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┃                                          ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void f_screen::FailureScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                                          ┃");
	ScreenPrint(0, 7, "┃                                          ┃");
	ScreenPrint(0, 8, "┃                                          ┃");
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃                    미션 실패 !!!!        ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃                 ●┳━┓                 ┃");
	ScreenPrint(0, 15, "┃                   ┛  ┗                 ┃");
	ScreenPrint(0, 16, "┃                  ■■■■                ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃        다시 하시겠습니까? (y/n)          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void f_screen::ResultScreen(int* g_nStage)
{
	char string[100];
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃             □━━━□                   ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                                          ┃");
	ScreenPrint(0, 7, "┃                                          ┃");
	sprintf(string, "┃      성공한 스테이지 :  %2d               ┃", *g_nStage + 1);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃   ___▒▒▒___                           ┃");
	ScreenPrint(0, 12, "┃     (*^  ^*)                             ┃");
	ScreenPrint(0, 13, "┃ =====○==○=====                         ┃");
	ScreenPrint(0, 14, "┃                                          ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                      ┗●┛              ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}