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

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length < Enemy.GetSensingLength())
	{
		return new EngagingMode();
	}

	return nullptr;
}
