#include "EventManager.h"

EventManager::EventManager()
{
	wavePattern = new WavePatternRandom();
	normState = false;
}

EventManager::~EventManager()
{
	delete wavePattern;
}

bool EventManager::Update(EnemyManager &EnemyManager, DecorationManager & DecorationManager, StageBorder & StageBorder)
{
	timeLimit_Frame--;

	if (timeLimit_Frame <= 0)
	{
		timeLimit_Frame = 0;
		return false;
		//リザルト移行
	}

	if (wavePattern != nullptr)
	{
		WavePatternBase *NextPattern;
		NextPattern = wavePattern->WaveProcessing(EnemyManager, DecorationManager, StageBorder);
		if (NextPattern != nullptr)
		{
			delete wavePattern;
			wavePattern = NextPattern;
		}
	}

	if (nowCnt >= normCnt)
	{
		normState = true;
	}
	return true;
}

void EventManager::AddScore(int Score)
{
	score = Score;
}

void EventManager::DoDecorate(DecorationID ID)
{
	nowCnt += 1;
}


void EventManager::SetTimeLimit(int TimeLimit_Frame)
{
	timeLimit_Frame = TimeLimit_Frame;
}

void EventManager::SetNorm(int Norm)
{
	normCnt = Norm;
}

int EventManager::GetRemainingTime_s(void)
{
	return timeLimit_Frame / GameFPS;
}

int EventManager::GetNowNormCnt(void)
{
	return nowCnt;
}

bool EventManager::GetNormState(void)
{
	return normState;
}

