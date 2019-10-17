#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
#include"Map/MapObjManager.h"
#include"Effect/EffectManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();
	//敵と雪玉の当たり判定	SnowBallManagerとEnemyManagerをポインタで渡す
	void SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
	//雪玉とMapオブジェの当たり判定	SnowBallManagerとMapObjManagerをポインタで渡す
	void SnowBalltoObj(SnowBallManager *snowBallManager, MapObjManager *MapObjManager);
};