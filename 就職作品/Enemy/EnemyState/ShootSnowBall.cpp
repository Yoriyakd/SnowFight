#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

EnemyStateBase * ShootSnowBall::Action(Enemy & Enemy)
{
	if (Enemy.GetJumpState() == false)		//ジャンプ中は撃たない
	{
		Enemy.ShootSnowBall();
		return new EngagingMode();
	}
	return nullptr;
}
