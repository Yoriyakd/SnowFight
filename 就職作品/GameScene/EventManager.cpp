#include "EventManager.h"

GameNormManager::GameNormManager() : normState(false), nowCnt(0)
{
}

GameNormManager::~GameNormManager()
{
}

//void GameNormManager::AddScore(int Score)
//{
//	score = Score;
//}

//void GameNormManager::DoDecorate(CarryObjectID ID)
//{
//	nowCnt += 1;
//}

void GameNormManager::DoDecorate(void)
{
	nowCnt += 1;

	if (nowCnt >= normCnt)
	{
		normState = true;
	}
}

void GameNormManager::SetNorm(int Norm)
{
	normCnt = Norm;
}

int GameNormManager::GetNowNormCnt(void)
{
	return nowCnt;
}

bool GameNormManager::GetNormState(void)
{
	return normState;
}
