#include "GameTime.h"

int GameTime::timeLimit_Frame;

GameSceneState GameTime::AddUpdate()
{
	timeLimit_Frame--;

	if (timeLimit_Frame <= 0)
	{
		timeLimit_Frame = 0;
		return TIME_UP_EFFECT;	//リザルト移行
	}
	return IN_GAME;
}

void GameTime::PlayerTakeDamage(int _Penalty)
{
	timeLimit_Frame -= _Penalty * GAME_FPS;
}

void GameTime::SetTimeLimit(int TimeLimit_Frame)
{
	timeLimit_Frame = TimeLimit_Frame;
}

int GameTime::GetRemainingTime_s(void)
{
	return timeLimit_Frame / GAME_FPS;
}
