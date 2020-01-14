#include "PlayerSearchState.h"
#include"../Enemy.h"
#include"EngagingMode.h"

EnemyStateBase * PlayerSearchState::Action(Enemy &Enemy)
{
	float Length;
	const float SensingLength = 40.0f;

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length < SensingLength)
	{
		return new EngagingMode();
	}


	Enemy.FrontJump();
	

	return nullptr;
}
