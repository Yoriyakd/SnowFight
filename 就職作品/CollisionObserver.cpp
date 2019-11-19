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

					if (enemyManager->enemy[i]->TakeDamage(1) == false)		//falseが返ってきたら
					{
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
						enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
						i--;						//きえた分詰める
					}

					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					j--;						//きえた分詰める
					break;
				}
			}
		}
	}
}

void CollisionObserver::SnowBalltoObj(SnowBallManager *snowBallManager, MapObjManager *mapObjManager)
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

void CollisionObserver::PlayertoObj(PlayerCamera * PlayerCam, MapObjManager * MapObjManager)
{
	D3DXVECTOR3 PlayerPosTmp, PlayerMoveVecTmp;
	PlayerPosTmp = PlayerCam->GetPos();
	PlayerPosTmp.y = 0;				//Y座標が頭の位置なので変更
	PlayerMoveVecTmp = PlayerCam->GetmoveVec();

	for (unsigned int i = 0; i < MapObjManager->mapObj.size(); i++)
	{
		

		CollisionDetectionType TypeTmp;
		TypeTmp = MapObjManager->mapObj[i]->GetCollisionDetectionType();

		if (TypeTmp == Ray)				//設計がわるすぎる	☆
		{
			D3DXMATRIX ObjMatTmp;
			ObjMatTmp = MapObjManager->mapObj[i]->GetMat();
			D3DXMATRIX invMat;

			D3DXMatrixInverse(&invMat, NULL, &ObjMatTmp);

			D3DXVECTOR3 LocalPos, LocalVec;

			D3DXVec3TransformCoord(&LocalPos, &PlayerPosTmp, &invMat);		//それぞれの逆行列を作る
			D3DXVec3TransformNormal(&LocalVec, &PlayerMoveVecTmp, &invMat);
			D3DXVec3Normalize(&LocalVec, &LocalVec);


			BOOL hit; float meshDis; DWORD PolyNo; XFILE ObjMesh;

			ObjMesh = MapObjManager->mapObj[i]->GetMesh();

			D3DXIntersect(ObjMesh.lpMesh, &LocalPos, &LocalVec, &hit, &PolyNo, NULL, NULL, &meshDis, NULL, NULL);
			if (hit == TRUE)
			{
				WORD *pI;
				ObjMesh.lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);
				DWORD vertexNo[3];
				vertexNo[0] = *(pI + PolyNo * 3 + 0);		//PolyNo番目の構成する1つめのインデックス
				vertexNo[1] = *(pI + PolyNo * 3 + 1);
				vertexNo[2] = *(pI + PolyNo * 3 + 2);

				CLONEVERTEX *pV;

				ObjMesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

				D3DXVECTOR3 vPos[3];

				vPos[0] = (pV + vertexNo[0])->Pos;			//上で手に入れたインデックスを用いてその頂点の座標を得る
				vPos[1] = (pV + vertexNo[1])->Pos;
				vPos[2] = (pV + vertexNo[2])->Pos;

				ObjMesh.lpMesh->UnlockVertexBuffer();

				D3DXVECTOR3 Vec1, Vec2;

				Vec1 = vPos[1] - vPos[0];			//2辺用意
				Vec2 = vPos[2] - vPos[0];

				D3DXVECTOR3 ObjNormal;

				D3DXVec3Cross(&ObjNormal, &Vec1, &Vec2);	//ポリゴンの2辺の外積を求め法線を求める
				D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMatTmp);		//表示に使う行列を使ってグローバル座標をを求めている
				D3DXVec3Normalize(&ObjNormal, &ObjNormal);	//正規化

				float Dot;
				Dot = D3DXVec3Dot(&ObjNormal, &-PlayerMoveVecTmp);		//内積を求める	両方長さ1なのでコサインθになる
				float Limit;					//三角形の斜辺の長さ
				Limit = 3 / Dot;				//3は壁から離したい距離
				if (Limit < 0)Limit *= -1;		//逆から壁に接近した場合-になるので反転

				if (meshDis < Limit)
				{
					D3DXVECTOR3 PushVec;
					PushVec = ObjNormal * ((Limit - meshDis) * Dot);	//法線方向に押し出し
					PushVec.y = 0;									//斜めの壁にぶつかると地面に埋まるのでy方向の移動を0にしている
					PlayerCam->PushPos(&PushVec);
				}
			}
		}
		else
		{
			if (TypeTmp == Circles)
			{
				D3DXVECTOR3 TargetVec, ObjPosTmp;
				ObjPosTmp = MapObjManager->mapObj[i]->GetPos();

				TargetVec = D3DXVECTOR3(PlayerPosTmp.x, 0.0f, PlayerPosTmp.z) - ObjPosTmp;		//Y座標を無視する

				float TargetLength;

				TargetLength = D3DXVec3Length(&TargetVec);

				const float PlayerRadius = 2.0f, ObjRadius = MapObjManager->mapObj[i]->GetRadius();

				if (TargetLength < PlayerRadius + ObjRadius)		//仮☆
				{
					D3DXVec3Normalize(&TargetVec, &TargetVec);
					TargetVec *= (PlayerRadius + ObjRadius - TargetLength);
					D3DXMATRIX TmpMat;

					PlayerCam->PushPos(&TargetVec);
				}
			}
		}
	}
}