#include "LookForPlayerAnime.h"
#include"../Enemy.h"
#include"EngagingMode.h"

LookForPlayerAnime::LookForPlayerAnime() : frameCnt(0)
{
}

EnemyStateBase * LookForPlayerAnime::Action(Enemy & Enemy)
{
	frameCnt++;
	Enemy.Spin((float)(sin(frameCnt / 30) * 2));

	if (frameCnt > 4 * GameFPS)
	{
		Enemy.Spin((float)(rand() % 30));
		return new PlayerSearchState();
	}

	float Length;
	const float SensingLength = 60.0f;

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length < SensingLength)
	{
		return new EngagingMode();
	}

	return nullptr;
}
