#include "PlayerSearchState.h"
#include"../Enemy.h"

EnemyStateBase * PlayerSearchState::Action(Enemy &Enemy)
{
	if (Enemy.GetJumpState() == false)
	{
		Enemy.FrontJump();
	}

	return nullptr;
}
