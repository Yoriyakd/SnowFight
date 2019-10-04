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
			if (snowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//�v���C���[�̋��Ȃ���s
			{
				
				//---------------------------------------------------------------
				//�K�v�Ȓl��p��

				CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;

				enemyManager->enemy[i]->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*�����蔻��̋��̃f�[�^�擾*/
				snowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
				//---------------------------------------------------------------

				if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
				{
					delete enemyManager->enemy[i];
					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
					j--;						//���������l�߂�
					i--;						//���������l�߂�
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
			//�K�v�Ȓl��p��

			XFILE MeshTmp;
			D3DXMATRIX MeshMat;
			D3DXVECTOR3 RayVec, RayPos;
			float MeshDis;

			MeshTmp = wallManager->wall[j]->GetMesh();
			MeshMat = wallManager->wall[j]->GetWallMat();
			RayPos = snowBallManager->snowBall[i]->GetPos();
			RayVec = snowBallManager->snowBall[i]->GetMoveVec();

			//---------------------------------------------------------------
			
			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
			{
				CollisionSphere SnowBallSphere;
				snowBallManager->snowBall[i]->GetCollisionSphere(&SnowBallSphere);

					if (MeshDis < SnowBallSphere.radius)										//���������a�ȉ��Ȃ�
					{
						delete snowBallManager->snowBall[i];
						snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
						i--;				//���������l�߂�
						break;
					}
			}
		}
	}
}
