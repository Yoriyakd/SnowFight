#pragma once
#include"EnemyStateBase.h"
class ShootSnowBall : public EnemyStateBase{
public:
	EnemyStateBase* Action(Enemy &Enemy);
};