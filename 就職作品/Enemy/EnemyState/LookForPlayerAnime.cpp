#include "LookForPlayerAnime.h"
#include"../Enemy.h"

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

	return nullptr;
}
