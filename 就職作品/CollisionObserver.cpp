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

				CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;//Aが上Bが下

				enemyManager->enemy[i]->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*当たり判定の球のデータ取得*/
				snowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*当たり判定の球のデータ取得*/
				//---------------------------------------------------------------

				if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
				{
					//SnowFragエフェクト呼ぶ
					effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

					//-------------------------------------------------------------
					//EnemyDeathAnime再生開始
					//-------------------------------------------------------------
					//引数として渡す変数を一時的に宣言
					D3DXMATRIX TmpAnimeMat;
					XFILE TmpAnimeMesh;
					D3DXVECTOR3 SnowBallVec;

					TmpAnimeMat = enemyManager->enemy[i]->GetMat();		//行列
					TmpAnimeMesh = enemyManager->enemy[i]->GetMesh();	//Mesh
					SnowBallVec = snowBallManager->snowBall[j]->GetMoveVec();	//雪玉の移動ベクトルをもらう

					effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));
					//-------------------------------------------------------------

					//死んだインスタンス削除
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

void CollisionObserver::SnowBalltoObj(SnowBallManager * snowBallManager, MapObjManager * mapObjManager)
{
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			//---------------------------------------------------------------
			//必要な値を用意

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
			
			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//メッシュに対してレイ判定
			{
				CollisionSphere SnowBallSphere;
				snowBallManager->snowBall[i]->GetCollisionSphere(&SnowBallSphere);

					if (MeshDis < SnowBallSphere.radius)										//距離が半径以下なら
					{
						//SnowFragエフェクト呼ぶ
						effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[i]->GetPos()));

						//死んだインスタンス削除
						delete snowBallManager->snowBall[i];
						snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
						i--;				//きえた分詰める
						break;
					}
			}
		}
	}
}
