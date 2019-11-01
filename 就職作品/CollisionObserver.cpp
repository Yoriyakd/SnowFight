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

				CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;//A����B����

				enemyManager->enemy[i]->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*�����蔻��̋��̃f�[�^�擾*/
				snowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
				//---------------------------------------------------------------

				if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
				{
					//SnowFrag�G�t�F�N�g�Ă�
					effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

					//-------------------------------------------------------------
					//EnemyDeathAnime�Đ��J�n
					//-------------------------------------------------------------
					//�����Ƃ��ēn���ϐ����ꎞ�I�ɐ錾
					D3DXMATRIX TmpAnimeMat;
					XFILE TmpAnimeMesh;
					D3DXVECTOR3 SnowBallVec;

					TmpAnimeMat = enemyManager->enemy[i]->GetMat();		//�s��
					TmpAnimeMesh = enemyManager->enemy[i]->GetMesh();	//Mesh
					SnowBallVec = snowBallManager->snowBall[j]->GetMoveVec();	//��ʂ̈ړ��x�N�g�������炤

					effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));
					//-------------------------------------------------------------

					//���񂾃C���X�^���X�폜
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

void CollisionObserver::SnowBalltoObj(SnowBallManager * snowBallManager, MapObjManager * mapObjManager)
{
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			//---------------------------------------------------------------
			//�K�v�Ȓl��p��

			XFILE MeshTmp;
			D3DXMATRIX MeshMat;
			D3DXVECTOR3 RayVec, RayPos;
			float MeshDis;

			MeshTmp = mapObjManager->mapObj[j]->GetMesh();
			MeshMat = mapObjManager->mapObj[j]->GetMat();
			RayPos = snowBallManager->snowBall[i]->GetPos();
			RayVec = snowBallManager->snowBall[i]->GetMoveVec();
			D3DXVec3Normalize(&RayVec, &RayVec);

			//---------------------------------------------------------------
			
			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
			{
				CollisionSphere SnowBallSphere;
				snowBallManager->snowBall[i]->GetCollisionSphere(&SnowBallSphere);

					if (MeshDis < SnowBallSphere.radius)										//���������a�ȉ��Ȃ�
					{
						//SnowFrag�G�t�F�N�g�Ă�
						effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[i]->GetPos()));

						//���񂾃C���X�^���X�폜
						delete snowBallManager->snowBall[i];
						snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
						i--;				//���������l�߂�
						break;
					}
			}
		}
	}
}
