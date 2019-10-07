#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
#include"Map/WallManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();
	//敵と雪玉の当たり判定	SnowBallManagerとEnemyManagerをポインタで渡す
	void SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
	//雪玉と壁の当たり判定	SnowBallManagerとWallManagerをポインタで渡す
	void SnowBalltoWall(SnowBallManager *snowBallManager, WallManager *wallManager);
};