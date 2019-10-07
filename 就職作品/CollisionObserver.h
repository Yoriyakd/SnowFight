#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
#include"Map/WallManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();
	//�G�Ɛ�ʂ̓����蔻��	SnowBallManager��EnemyManager���|�C���^�œn��
	void SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
	//��ʂƕǂ̓����蔻��	SnowBallManager��WallManager���|�C���^�œn��
	void SnowBalltoWall(SnowBallManager *snowBallManager, WallManager *wallManager);
};