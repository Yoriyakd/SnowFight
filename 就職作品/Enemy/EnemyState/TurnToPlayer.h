#pragma once
#include"EnemyStateBase.h"
#include<d3dx9.h>
class TurnToPlayer : public EnemyStateBase {
public:
	EnemyStateBase* Action(Enemy &Enemy);
};