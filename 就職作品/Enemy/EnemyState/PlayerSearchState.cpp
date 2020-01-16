#include "PlayerSearchState.h"
#include"../Enemy.h"
#include"EngagingMode.h"
#include"LookForPlayerAnime.h"

EnemyStateBase * PlayerSearchState::Action(Enemy &Enemy)
{
	float Length;
	const float SensingLength = 60.0f;

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length < SensingLength)
	{
		return new EngagingMode();
	}

	if (rand() % 250 < 1)
	{
		return new LookForPlayerAnime();
	}

	Enemy.FrontJump();
	

	return nullptr;
}
