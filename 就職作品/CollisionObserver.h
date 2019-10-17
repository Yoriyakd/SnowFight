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
	//�G�Ɛ�ʂ̓����蔻��	SnowBallManager��EnemyManager���|�C���^�œn��
	void SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager);
	//��ʂ�Map�I�u�W�F�̓����蔻��	SnowBallManager��MapObjManager���|�C���^�œn��
	void SnowBalltoObj(SnowBallManager *snowBallManager, MapObjManager *MapObjManager);
};