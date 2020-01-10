#include "Enemy.h"
#include"../GameScene/GameScene.h"//☆

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos) : jumpState(false), nowState(new PlayerSearchState())
{
	bodyMesh = GetResource.GetXFILE(EnemyBody_M);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	hatMesh = GetResource.GetXFILE(EnemyHat_M);
	D3DXMatrixTranslation(&hatOffsetMat, 0.0f, 6.6f, -0.3f);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//生まれたときランダムな角度に (かまくらから生まれるときはこれじゃダメだから変える
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	D3DXMatrixRotationX(&hatRotMat, D3DXToRadian(-10));

	hatMat = hatRotMat * hatOffsetMat * mat;

	MoveInterval = 0;	//初期値は0(すぐ動く)
	freeMoveCnt = (float)(rand() % 3) * GameFPS;	//初期化
	limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//minLength~maxLengthの間で初期化	最大値がmaxLengthになるように+1している

	HP = 3;
}

Enemy::~Enemy()
{
	delete nowState;
}

bool Enemy::Update(Player & Player, SnowBallManager & SnowBallManager, StageBorder & StageBorder)
{
	moveVec.y -= 0.001f;

	D3DXMATRIX MoveMat;
	D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);


	mat = MoveMat * mat;

	if (mat._42 < 0.0f)
	{
		mat._42 = 0.0f;
		jumpState = false;
	}


	if (nowState != nullptr)
	{
		EnemyStateBase *NextState;
		NextState = nowState->Action(*this);
		if (NextState != nullptr)
		{
			delete nowState;
			nowState = NextState;
		}
	}
	

	

	//D3DXVECTOR3 TragetPos, TragetVec;

	//TragetPos = Player.GetPlayerPos();
	//TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める

	//float TragetLength, LimitLength = 50.0f;
	//TragetLength = D3DXVec3Length(&TragetVec);		//プレイヤーとの距離を求める

	//if (TragetLength < LimitLength)		//距離がLimitLength未満なら交戦Modeになる
	//{
	//	EngagingMode(TragetPos ,SnowBallManager);
	//}
	//else
	//{
	//	FreeMode();						//範囲外で即追跡終了は変えたい
	//}

	StageBorderProcessing(StageBorder);			//移動処理のあとに呼ぶ

	hatMat = hatRotMat * hatOffsetMat * mat;

	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&bodyMesh);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &hatMat);
	DrawMesh(&hatMesh);
}

const D3DXVECTOR3 Enemy::GetPos(void)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

const D3DXMATRIX Enemy::GetMat(void)
{
	return mat;
}



void Enemy::GetCollisionSphere(CollisionSphere * CollisionSphereA, CollisionSphere * CollisionSphereB)
{
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2.0f, mat._43);		//Y座標要調整☆	
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 4.7f, mat._43);
	CollisionSphereA->radius = SphereRadiusHead;
	CollisionSphereB->radius = SphereRadiusBody;
}

bool Enemy::GetJumpState()
{
	return jumpState;
}

D3DXMATRIX Enemy::GetHatMat(void)
{
	return hatMat;
}

float Enemy::GetHatRadius(void)
{
	return hatRadius;
}

float Enemy::GetHatHight(void)
{
	return hatHight;
}

void Enemy::CheckOverlapEnemies(const D3DXVECTOR3 *TargetPos)
{

	D3DXVECTOR3 TargetVec;

	TargetVec = D3DXVECTOR3(mat._41, 0.0f, mat._43) - D3DXVECTOR3(TargetPos->x, 0.0f, TargetPos->z);		//Y座標を無視する

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	float Radius = 3;	//変数化
	if (TargetLength < Radius + Radius)
	{
		D3DXVec3Normalize(&TargetVec, &TargetVec);
		TargetVec *= (Radius + Radius - TargetLength);
		D3DXMATRIX TmpMat;
		D3DXMatrixTranslation(&TmpMat, TargetVec.x, TargetVec.y, TargetVec.z);

		mat = mat * TmpMat;
	}
}

bool Enemy::TakeDamage(int Damage)
{
	//damageFlag = true;
	//damageEffectCnt = 10;	//10フレーム
	HP -= Damage;
	if (HP <= 0)
	{
		return false;
	}
	return true;
}

//=====================================
//privateメソッド
//=====================================

void Enemy::ShootSnowBall(const float TragetAng, SnowBallManager &snowBallManager)
{
	D3DXVECTOR3 PosTmp(3, 3, 0);
	D3DXVec3TransformCoord(&PosTmp, &PosTmp, &mat);

	ThrowingInitValue ValueTmp;
	ValueTmp.shootPos = PosTmp;
	
	ValueTmp.XAxisAng = 30;								/*要調整*/	//☆
	ValueTmp.YAxisAng = TragetAng;						/*要調整*/
	ValueTmp.powerRate = 40.0f;							/*要調整*/


	if (ShootCoolTime < 0)
	{
		snowBallManager.SetSnowBall(&ValueTmp, ENEMY_ID);
		ShootCoolTime = 3 * GameFPS;
	}
	ShootCoolTime--;
}

void Enemy::EngagingMode(D3DXVECTOR3 TragetPos, SnowBallManager &SnowBallManager)
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


	if (NowFrontVec.x < 0)			//角度の正負チェック	(外積を使わない方法で求めている)
	{
		NowAng *= -1;
	}

	//------------------------------------------------------
	//プレイヤーとの角度を求める
	//------------------------------------------------------

	D3DXVECTOR3 TragetVec;


	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める

	D3DXVec3Normalize(&TragetVec, &TragetVec);				//ベクトル正規化

	float TragetDot;

	TragetDot = D3DXVec3Dot(&TragetVec, &DefaultVec);		//初期ベクトルとプレイヤーへのベクトルから内積を求める

	if (TragetDot > 1)TragetDot = 1;						//内積の値が1より大きくならないように
	if (TragetDot < -1)TragetDot = -1;						//内積の値が-1より小さくくならないように

	float TragetAng;

	TragetAng = D3DXToDegree(acos(TragetDot));				//プレイヤーと初期の角度を求める

	if (TragetVec.x < 0)									//角度の正負チェック	(外積を使わない方法で求めている)
	{
		TragetAng *= -1;
	}


	//------------------------------------------------------
	//角度の差を求める
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

	//---------------------------------------------------
	//必要回転量が一回の回転量より小さい場合回転しすぎないようにする
	//---------------------------------------------------

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
	//---------------------------------------------------
	//移動処理
	//---------------------------------------------------

	D3DXMATRIX MoveMat;

	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める	上で正規化してしまっているのでもう一度求める

	float TragetLength;

	if (rand() % 1000 < 1)		//0.1%の確立で再抽選
	{
		limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//最大値がmaxLengthになるように + 1している
	}

	TragetLength = D3DXVec3Length(&TragetVec);		//プレイヤーとの距離を求める


	if (rand() % 100 < 1)
	{
		int RandCase;
		switch (RandCase = rand() % 3)
		{
		case 0:
			moveVec.x = 0.0f;
			break;
		case 1:
			moveVec.x = 0.2f;
			break;
		case 2:
			moveVec.x = -0.2f;
			break;
		}

	}

	if (TragetLength < limitLength)
	{
		moveVec.z = -0.2f;
		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
	}
	else
	{
		moveVec.z = 0.2f;
		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
	}

	mat = MoveMat * mat;

	ShootSnowBall(TragetAng, SnowBallManager);
}

void Enemy::FreeMode(void)
{
	D3DXMATRIX MoveMat;
	static const int MaxInterval = 10;			//間隔の最大値
	static const int MinInterval = 5;			//間隔の最小値

	if (MoveInterval < 0)
	{

		D3DXMatrixTranslation(&MoveMat, 0.0f, 0.0f, 0.2f);
		mat = MoveMat * mat;
		freeMoveCnt--;
		if (freeMoveCnt < 0)				//規定の時間動いたら次動くまでの時間を再設定
		{
			MoveInterval = (float)(rand() % (MaxInterval + 1 - MinInterval) + MinInterval) * GameFPS;			//ランダムで次動くまでの時間を決める	最大値がMaxIntervalになるように+1している
			freeMoveCnt = (float)(rand() % 3) * GameFPS;
		}
	}

	MoveInterval--;

}

void Enemy::StageBorderProcessing(StageBorder & StageBorder)
{
	//ステージ境界の処理
	if (mat._43 > StageBorder.Top)
	{
		mat._43 += StageBorder.Top - mat._43;
	}

	if (mat._43 < StageBorder.Bottom)
	{
		mat._43 += StageBorder.Bottom - mat._43;
	}

	if (mat._41 < StageBorder.Left)
	{
		mat._41 += StageBorder.Left - mat._41;
	}

	if (mat._41 > StageBorder.Right)
	{
		mat._41 += StageBorder.Right - mat._41;
	}
}

void Enemy::FrontJump(void)
{
	D3DXVECTOR3 JumpVec(0.0f, 0.05f, 0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
	jumpState = true;
}

void Enemy::BackJump(void)
{
	D3DXVECTOR3 JumpVec(0.0f, 1.0f, -0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
	jumpState = true;
}
