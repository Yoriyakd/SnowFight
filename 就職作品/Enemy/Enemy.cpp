#include "Enemy.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;

//=====================================
//privateメソッド
//=====================================

void Enemy::ShootSnowBall(float TragetAng)
{
	SnowBallInitValue ValueTmp;
	ValueTmp.shootPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	ValueTmp.shootPos.y += 3;							//発射位置調整(変数化)
	ValueTmp.XAxisAng = 30;
	ValueTmp.YAxisAng = TragetAng;
	ValueTmp.powerRate = 20.0f;
	ValueTmp.id = ENEMY_ID;

	static int CoolTime = 3 * GameFPS;
	if (CoolTime < 0)
	{
		snowBallManager->SetSnowBall(&ValueTmp);
		CoolTime = 3 * GameFPS;
	}
	CoolTime--;
}

void Enemy::EngagingMode(void)
{
	//------------------------------------------------------
	//現在の角度を求める
	//------------------------------------------------------



	D3DXVECTOR3 NowFrontVec, DefaultVec(0, 0, 1);

	D3DXVec3TransformNormal(&NowFrontVec, &DefaultVec, &mat);	//現在の方向ベクトルを求める

	D3DXVec3Normalize(&NowFrontVec, &NowFrontVec);				//方向ベクトル正規化

	float NowDot;

	NowDot = D3DXVec3Dot(&NowFrontVec, &DefaultVec);			//初期ベクトルと現在の方向ベクトルで内積を求め現在の角度を求める

	if (NowDot > 1)NowDot = 1;									//内積の値が1より大きくならないように
	if (NowDot < -1)NowDot = -1;								//内積の値が-1より小さくくならないように

	float NowAng;

	NowAng = D3DXToDegree(acos(NowDot));

	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &DefaultVec, &NowFrontVec);			//外積を求め

	if (RotAxis.y < 0)											//外積の方向が負なら
	{
		NowAng *= -1;											//角度は負(反時計回り)
	}

	//------------------------------------------------------
	D3DXVECTOR3 TragetVec, TragetPos;

	TragetPos = player->GetPlayerPos();

	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める

	D3DXVec3Normalize(&TragetVec, &TragetVec);				//ベクトル正規化

	float TragetDot;

	TragetDot = D3DXVec3Dot(&TragetVec, &DefaultVec);		//初期ベクトルとプレイヤーへのベクトルから内積を求める

	if (TragetDot > 1)TragetDot = 1;						//内積の値が1より大きくならないように
	if (TragetDot < -1)TragetDot = -1;						//内積の値が-1より小さくくならないように

	float TragetAng;

	TragetAng = D3DXToDegree(acos(TragetDot));				//プレイヤーと初期の角度を求める

	D3DXVec3Cross(&RotAxis, &DefaultVec, &TragetVec);		//外積を求める

	if (RotAxis.y < 0)										//外積の方向が負なら
	{
		TragetAng *= -1;									//角度は負(反時計回り)
	}


	//------------------------------------------------------
	float MoveAng;

	MoveAng = TragetAng - NowAng;							//初期の角度と今の角度の差を求める

	if (MoveAng > 180)			//鋭角への変換
	{
		MoveAng -= 360;
	}

	if (MoveAng < -180)
	{
		MoveAng += 360;
	}


	if (MoveAng >= 0)
	{
		float RotSpeed = 3;
		if (MoveAng < RotSpeed)
		{
			RotSpeed = MoveAng;
		}
		D3DXMatrixRotationY(&rotMat, D3DXToRadian(RotSpeed));
	}

	if (MoveAng <= 0)
	{
		float RotSpeed = -3;
		if (MoveAng > RotSpeed)
		{
			RotSpeed = MoveAng;
		}
		D3DXMatrixRotationY(&rotMat, D3DXToRadian(RotSpeed));
	}
	mat = rotMat * mat;

	ShootSnowBall(TragetAng);
}

void Enemy::FreeMode(void)
{
}

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Enemy/EnemyBody.x");
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

Enemy::~Enemy()
{
}

bool Enemy::Update(SnowBallManager *SnowBallManager)
{
	snowBallManager = SnowBallManager;
	D3DXVECTOR3 TragetPos, TragetVec;

	TragetPos = player->GetPlayerPos();
	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める

	float TragetLength, LimitLength = 80.0f;
	TragetLength = D3DXVec3Length(&TragetVec);		//プレイヤーとの距離を求める

	if (TragetLength < LimitLength)		//距離がLimitLength未満なら交戦Modeになる
	{
		EngagingMode();
	}
	
	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

}

D3DXVECTOR3 Enemy::GetPos(void)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

void Enemy::GetCollisionSphere(CollisionSphere * CollisionSphereA, CollisionSphere * CollisionSphereB)
{
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2, mat._43);		//Y座標要調整
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 5, mat._43);
	CollisionSphereA->radius = 3;
	CollisionSphereB->radius = 3;
}
