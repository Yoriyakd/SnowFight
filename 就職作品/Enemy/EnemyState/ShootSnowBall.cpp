#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

EnemyStateBase* ShootSnowBall::Action(Enemy& Enemy)
{
	if (Enemy.GetJumpState() == false)		//ジャンプ中は撃たない
	{
		//振りかぶり
		if (!WindUp(Enemy))return nullptr;		//終了まで行う
		Enemy.ShootSnowBall();
		return new EngagingMode();
	}
	return nullptr;
}

bool ShootSnowBall::WindUp(Enemy& Enemy)
{

	return true;		//動きが終了するとtrueを返す
	return false;
}

