#include "EventManager.h"

EventManager::EventManager()
{
	normState = false;
	nowCnt = 0;
}

EventManager::~EventManager()
{
}

bool EventManager::TimeUpdate()
{
	timeLimit_Frame--;

	if (timeLimit_Frame <= 0)
	{
		timeLimit_Frame = 0;
		return false;
		//ƒŠƒUƒ‹ƒgˆÚs
	}

	if (nowCnt >= normCnt)
	{
		normState = true;
	}

	return true;
}

//void EventManager::AddScore(int Score)
//{
//	score = Score;
//}

void EventManager::DoDecorate(CarryObjectID ID)
{
	nowCnt += 1;
}

void EventManager::PlayerTakeDamage()
{
	timeLimit_Frame -= 3 * GameFPS;
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
