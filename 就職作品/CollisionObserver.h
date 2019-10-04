#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
#include"Map/WallManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();

	void SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
	void SnowBalltoWall(SnowBallManager *snowBallManager, WallManager *wallManager);
};