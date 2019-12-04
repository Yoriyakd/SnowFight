#include "EventManager.h"

EventManager::EventManager()
{
	wavePattern = new WavePattern1();
}

EventManager::~EventManager()
{
	delete wavePattern;
}

bool EventManager::Update()
{
	timeLimit_Frame--;

	if (timeLimit_Frame <= 0)
	{
		timeLimit_Frame = 0;
		return false;
		//ƒŠƒUƒ‹ƒgˆÚs
	}

	if (wavePattern != nullptr)
	{
		WavePatternBase *NextPattern;
		NextPattern = wavePattern->WaveProcessing();
		if (NextPattern != nullptr)
		{
			delete wavePattern;
			wavePattern = NextPattern;
		}
	}
	return true;
}

void EventManager::AddScore(int Score)
{
	score = Score;
}

void EventManager::SetTimeLimit(int TimeLimit_Frame)
{
	timeLimit_Frame = TimeLimit_Frame;
}

int EventManager::GetRemainingTime_s(void)
{
	return timeLimit_Frame / GameFPS;
}

