#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

bool CollisionObserver::SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager)
{
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (snowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//�v���C���[�̋��Ȃ���s
			{
				D3DXVECTOR3 EnemyPosTmp = enemyManager->enemy[i]->GetPos(),
					SnowBall_PPosTmp = snowBallManager->snowBall[j]->GetPos();

				if (CollisionDetection(SnowBall_PPosTmp, 1.5, EnemyPosTmp, 3))		//���a���Ƃŕϐ���
				{
					delete enemyManager->enemy[i];
					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
					j--;
					i--;
				}
			}
		}
	}
	return false;
}
