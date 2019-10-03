#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();

	bool SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
};