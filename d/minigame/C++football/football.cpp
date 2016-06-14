#include"football.h"

football::football() :g_nStage(-1), g_nLength(0), g_nGoal(0), g_nBallCount(0), g_nGoalBallCount(0), g_nIsGoal(0)
{
	g_strPlayer = "¦±¦¬¡Ü¦¬¦°";
	g_sStageInfo[0] = { 3, 1000 * 20, 1, 20, 3, 300, 1 };
	g_sStageInfo[1] = { 10, 1000 * 30, 2, 20, 5, 300, 1 };
}