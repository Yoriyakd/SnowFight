#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

bool CollisionObserver::SnowBalltoEnemyHat(SnowBall *SnowBall, Enemy *Enemy)
{
	if (SnowBall->GetID() == ENEMY_ID)return false;		//IDが敵のものなら早期リターン

	float HatRadius, HatHight, SnowBallRadius;
	D3DXVECTOR3 SnowBallPos;
	D3DXMATRIX HatMat;

	HatRadius = Enemy->GetHatRadius();
	HatHight = Enemy->GetHatHight();
	HatMat = Enemy->GetHatMat();

	SnowBallPos = SnowBall->GetPos();
	SnowBallRadius = SnowBall->GetSphereRadius();

	//無限円柱同士の判定
	D3DXVECTOR3 TargetVec;
	TargetVec = D3DXVECTOR3(HatMat._41, 0.0f, HatMat._43) - D3DXVECTOR3(SnowBallPos.x, 0.0f, SnowBallPos.z);		//Y座標を無視する

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	if (HatRadius + SnowBallRadius > TargetLength)		//距離が半径同士を足したものより小さいなら、高さの判定を行う
	{
		D3DXVECTOR3 HightVec;
		HightVec = D3DXVECTOR3(0.0f, HatMat._42, 0.0f) - D3DXVECTOR3(0.0f, SnowBallPos.y, 0.0f);

		float HightLength;

		HightLength = D3DXVec3Length(&HightVec);

		if (HatHight / 2.0f + SnowBallRadius > HightLength)
		{
			return true;
		}
	}
	
	return false;
}



bool CollisionObserver::SnowBalltoEnemy(SnowBall *SnowBall, Enemy *Enemy)		//呼び出す側でfor文を回すように変更する
{
	if (SnowBall->GetID() == ENEMY_ID)return false;		//IDが敵のものなら早期リターン
	//---------------------------------------------------------------
	//必要な値を用意
	CollisionSphere SnowBallSphre, EnemySphreHead, EnemySphreBody;//Aが上Bが下

	Enemy->GetCollisionSphere(&EnemySphreHead, &EnemySphreBody);		/*当たり判定の球のデータ取得*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*当たり判定の球のデータ取得*/
	//---------------------------------------------------------------

	if (SphereCollisionDetection(&SnowBallSphre, &EnemySphreHead) || SphereCollisionDetection(&SnowBallSphre, &EnemySphreBody))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionObserver::SnowBalltoObj(SnowBall *SnowBall, MapObj *MapObj)
{
	//必要な値を用意

	XFILE MeshTmp;
	D3DXMATRIX MeshMat;
	D3DXVECTOR3 LayVec, LayPos; D3DXVECTOR3 LayPosTmp;
	float MeshDis;

	MeshTmp = MapObj->GetMesh();
	MeshMat = MapObj->GetMat();
	LayPos = SnowBall->GetPos();
	LayVec = SnowBall->GetMoveVec();
	D3DXVec3Normalize(&LayVec, &LayVec);


	if (MeshCollisionDetection(&MeshTmp, &MeshMat, &LayPos, &LayVec, &MeshDis, nullptr))			//メッシュに対してレイ判定
	{
		CollisionSphere SnowBallSphere;
		SnowBall->GetCollisionSphere(&SnowBallSphere);

		if (MeshDis < SnowBallSphere.radius + 2.0f)										//距離が半径以下なら	(すこし大きめにとる)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void CollisionObserver::PlayertoObj(PlayerCamera *PlayerCam, MapObj *MapObj)
{
	D3DXVECTOR3 LayPos, LayVec;
	LayPos = PlayerCam->GetPos();
	LayPos.y = 0;						//Y座標が頭の位置なので変更
	LayVec = PlayerCam->GetmoveVec();
	
	D3DXVec3Normalize(&LayVec, &LayVec);

	CollisionDetectionType TypeTmp;
	TypeTmp = MapObj->GetCollisionDetectionType();

	if (TypeTmp == Ray)
	{
		D3DXMATRIX ObjMatTmp;
		ObjMatTmp = MapObj->GetMat();

		float MeshDis; DWORD PolyNo; XFILE ObjMesh;

		ObjMesh = MapObj->GetMesh();

		if(MeshCollisionDetection(&ObjMesh, &ObjMatTmp, &LayPos, &LayVec, &MeshDis, &PolyNo) == true)
		{
			D3DXVECTOR3 ObjNormal;

			GetPolyNormal(&ObjNormal, ObjMesh.lpMesh, &PolyNo);

			D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMatTmp);		//表示に使う行列を使ってポリゴン自体の回転を考慮したベクトルを求めている			※忘れない

			float Dot;
			Dot = D3DXVec3Dot(&ObjNormal, &-LayVec);		//内積を求める	両方長さ1なのでコサインθになる		法線の向きに合わせるためベクトルを反転させている

			float Limit;					//三角形の斜辺の長さ
			Limit = 3 / Dot;				//3は壁から離したい距離

			if (Limit < 0)Limit *= -1;		//逆から壁に接近した場合-になるので反転

			if (MeshDis < Limit)
			{
				D3DXVECTOR3 PushVec;
				PushVec = ObjNormal * ((Limit - MeshDis) * Dot);	//法線方向に押し出す長さを求める
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
			ObjPosTmp = MapObj->GetPos();

			TargetVec = D3DXVECTOR3(LayPos.x, 0.0f, LayPos.z) - ObjPosTmp;		//Y座標を無視する

			float TargetLength;

			TargetLength = D3DXVec3Length(&TargetVec);

			const float PlayerRadius = 2.0f, ObjRadius = MapObj->GetRadius();

			if (TargetLength < PlayerRadius + ObjRadius)		//仮☆プレイヤー半径が
			{
				D3DXVec3Normalize(&TargetVec, &TargetVec);
				TargetVec *= (PlayerRadius + ObjRadius - TargetLength);
				D3DXMATRIX TmpMat;

				PlayerCam->PushPos(&TargetVec);
			}
		}
	}
}

bool CollisionObserver::EnemySnowBalltoPlayer(Player *Player, SnowBall *SnowBall)
{
	if (SnowBall->GetID() == PLAYER_ID)return false;			//IDがプレイヤーのものなら早期リターン
	//---------------------------------------------------------------
	//必要な値を用意

	CollisionSphere SnowBallSphre, PlayerSphre;

	Player->GetCollisionSphere(&PlayerSphre);				/*当たり判定の球のデータ取得*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*当たり判定の球のデータ取得*/
	//---------------------------------------------------------------
	SnowBallSphre.radius += 3.0f;

	if (SphereCollisionDetection(&SnowBallSphre, &PlayerSphre))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CollisionObserver::DecorationToMapObj(DecorationBase *Decoration, MapObj *MapObj)
{
	if (Decoration->GetDecoratedState() == true)return;		//状態が飾られているならreturnで抜ける
	//---------------------------------------------------------------
	//必要な値を用意

	XFILE ObjMesh;
	D3DXMATRIX ObjMat;
	D3DXVECTOR3 LayVec, LayPos, MoveVec;
	float MeshDis;

	ObjMesh = MapObj->GetMesh();
	ObjMat = MapObj->GetMat();
	LayPos = Decoration->GetPos();
	MoveVec = LayVec = Decoration->GetMoveVec();

	D3DXVec3Normalize(&LayVec, &LayVec);

	DWORD PolyNo;

	if (MeshCollisionDetection(&ObjMesh, &ObjMat, &LayPos, &LayVec, &MeshDis, &PolyNo))			//メッシュに対してレイ判定
	{
		float Limit = 3.0f;

		D3DXVECTOR3 ObjNormal;

		GetPolyNormal(&ObjNormal, ObjMesh.lpMesh, &PolyNo);

		D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMat);		//表示に使う行列を使ってポリゴン自体の回転を考慮したベクトルを求めている			※忘れない

		float Dot;
		Dot = D3DXVec3Dot(&ObjNormal, &-LayVec);		//内積を求める	進行ベクトルと壁の法線 両方長さ1なのでコサインθになる

		Limit = 4.5f / Dot;				//離したい距離をDotで割って斜辺の長さを求めている

		if (Limit < 0)Limit *= -1;		//逆から壁に接近した場合-になるので反転

		if (MeshDis < Limit)										//距離が半径以下なら
		{
			if (MapObj->GetPossibleDecorate() == true)			//飾ることができるなら
			{
				D3DXVECTOR3 TreeDis;

				TreeDis = LayVec * MeshDis;			//Treeまでのベクトルを求める
				Decoration->DoDecorate(TreeDis);		//飾られている状態にする

			}
			else
			{
				D3DXVECTOR3 PushVec;

				PushVec = ObjNormal * ((Limit - MeshDis) * Dot);	//法線方向に押し出す長さを求める
				Decoration->PushPos(PushVec);		//1度法線方向に押し出す

				MoveVec = MoveVec + ((2 * Dot) * ObjNormal);			//移動ベクトルを壁の法線方向に2回押し出して反射ベクトルを求めている
				
				MoveVec *= 0.8f;		//反発係数を設定

				Decoration->SetMoveVec(MoveVec);
			}
		}
	}


}

void CollisionObserver::EnemyToMapObj(Enemy *Enemy, MapObj *MapObj)
{
	D3DXVECTOR3 TargetVec, ObjPosTmp, EnemyPos;

	EnemyPos = Enemy->GetPos();
	ObjPosTmp = MapObj->GetPos();

	TargetVec = D3DXVECTOR3(EnemyPos.x, 0.0f, EnemyPos.z) - ObjPosTmp;		//Y座標を無視する

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	const float EnemyRadius = Enemy->GetRadisu(), ObjRadius = MapObj->GetRadius();

	if (TargetLength < EnemyRadius + ObjRadius)
	{
		D3DXVec3Normalize(&TargetVec, &TargetVec);
		TargetVec *= (EnemyRadius + ObjRadius - TargetLength);
		D3DXMATRIX TmpMat;

		Enemy->PushedObj(TargetVec);
	}
}

void CollisionObserver::GetPolyNormal(D3DXVECTOR3 *ObjNormal, LPD3DXMESH ObjMesh, const DWORD *PolyNo)
{
	WORD *pI;
	ObjMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	DWORD vertexNo[3];
	vertexNo[0] = *(pI + *PolyNo * 3 + 0);		//PolyNo番目の構成する1つめのインデックス
	vertexNo[1] = *(pI + *PolyNo * 3 + 1);
	vertexNo[2] = *(pI + *PolyNo * 3 + 2);

	CLONEVERTEX *pV;

	ObjMesh->LockVertexBuffer(0, (LPVOID*)&pV);

	D3DXVECTOR3 vPos[3];

	vPos[0] = (pV + vertexNo[0])->Pos;			//上で手に入れたインデックスを用いてその頂点の座標を得る
	vPos[1] = (pV + vertexNo[1])->Pos;
	vPos[2] = (pV + vertexNo[2])->Pos;

	ObjMesh->UnlockVertexBuffer();

	D3DXVECTOR3 Vec1, Vec2;

	Vec1 = vPos[1] - vPos[0];			//2辺用意
	Vec2 = vPos[2] - vPos[0];

	D3DXVec3Cross(ObjNormal, &Vec1, &Vec2);	//ポリゴンの2辺の外積を求め法線を求める
	D3DXVec3Normalize(ObjNormal, ObjNormal);	//正規化		※ローカル座標の法線

	
}

