#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

EnemyStateBase * ShootSnowBall::Action(Enemy & Enemy)
{
	if (Enemy.GetJumpState() == false)		//ƒWƒƒƒ“ƒv’†‚ÍŒ‚‚½‚È‚¢
	{
		Enemy.ShootSnowBall();
		return new EngagingMode();
	}
	return nullptr;
}
