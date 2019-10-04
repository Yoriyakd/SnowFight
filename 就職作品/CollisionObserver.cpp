#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

void CollisionObserver::SnowBalltoEnemy(SnowBallManager *snowBallManager, EnemyManager *enemyManager)
{
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (snowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//プレイヤーの球なら実行
			{
				
				//---------------------------------------------------------------
				//必要な値を用意

				CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;

				enemyManager->enemy[i]->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*当たり判定の球のデータ取得*/
				snowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*当たり判定の球のデータ取得*/
				//---------------------------------------------------------------

				if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
				{
					delete enemyManager->enemy[i];
					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
					j--;						//きえた分詰める
					i--;						//きえた分詰める
					break;
				}
			}
		}
	}
}

void CollisionObserver::SnowBalltoWall(SnowBallManager * snowBallManager, WallManager * wallManager)
{
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		for (unsigned int j = 0; j < wallManager->wall.size(); j++)
		{
			//---------------------------------------------------------------
			//必要な値を用意

			XFILE MeshTmp;
			D3DXMATRIX MeshMat;
			D3DXVECTOR3 RayVec, RayPos;
			float MeshDis;

			MeshTmp = wallManager->wall[j]->GetMesh();
			MeshMat = wallManager->wall[j]->GetWallMat();
			RayPos = snowBallManager->snowBall[i]->GetPos();
			RayVec = snowBallManager->snowBall[i]->GetMoveVec();

			//---------------------------------------------------------------
			
			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//メッシュに対してレイ判定
			{
				CollisionSphere SnowBallSphere;
				snowBallManager->snowBall[i]->GetCollisionSphere(&SnowBallSphere);

					if (MeshDis < SnowBallSphere.radius)										//距離が半径以下なら
					{
						delete snowBallManager->snowBall[i];
						snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
						i--;				//きえた分詰める
						break;
					}
			}
		}
	}
}
