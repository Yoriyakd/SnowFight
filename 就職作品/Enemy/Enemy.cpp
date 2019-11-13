#include "Enemy.h"
#include"../GameScene/GameScene.h"


//=====================================
//privateメソッド
//=====================================

void Enemy::ShootSnowBall(float TragetAng)
{
	SnowBallInitValue ValueTmp;
	ValueTmp.shootPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	ValueTmp.shootPos.y += 3;							//発射位置調整(変数化)	手の位置から発射するようにする
	ValueTmp.XAxisAng = 30;								/*要調整*/	//☆
	ValueTmp.YAxisAng = TragetAng;						/*要調整*/
	ValueTmp.powerRate = 20.0f;							/*要調整*/
	ValueTmp.id = ENEMY_ID;

	
	if (ShootCoolTime < 0)
	{
		snowBallManager->SetSnowBall(&ValueTmp);
		ShootCoolTime = 3 * GameFPS;
	}
	ShootCoolTime--;
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


	if (NowFrontVec.x < 0)			//角度の正負チェック	(外積を使わない方法で求めている)
	{
		NowAng *= -1;
	}

	//------------------------------------------------------
	//プレイヤーとの角度を求める
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

	ShootSnowBall(TragetAng);
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

void Enemy::StageBorderProcessing(void)
{
	//ステージ境界の処理
	if (mat._43 > stageBorder.Top)
	{
		mat._43 += stageBorder.Top - mat._43;
	}

	if (mat._43 < stageBorder.Bottom)
	{
		mat._43 += stageBorder.Bottom - mat._43;
	}

	if (mat._41 < stageBorder.Left)
	{
		mat._41 += stageBorder.Left - mat._41;
	}

	if (mat._41 > stageBorder.Right)
	{
		mat._41 += stageBorder.Right - mat._41;
	}
}

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("EnemyBody.x");
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//生まれたときランダムな角度に (かまくらから生まれるときはこれじゃダメだから変える
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	MoveInterval = 0;	//初期値は0(すぐ動く)
	freeMoveCnt = (float)(rand() % 3) * GameFPS;	//初期化
	limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//minLength~maxLengthの間で初期化	最大値がmaxLengthになるように+1している

	HP = 5;

	color.a = 255;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	damageFlag = false;
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

	float TragetLength, LimitLength = 50.0f;
	TragetLength = D3DXVec3Length(&TragetVec);		//プレイヤーとの距離を求める

	if (TragetLength < LimitLength)		//距離がLimitLength未満なら交戦Modeになる
	{
		EngagingMode();
	}
	else
	{
		FreeMode();						//範囲外で即追跡終了は変えたい
	}

	StageBorderProcessing();			//移動処理のあとに呼ぶ

	if (damageFlag == true)
	{
		damageEffectCnt--;
		{
			if (damageEffectCnt < 0)
			{
				damageFlag = false;
			}
		}
	}
	
	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	if (damageFlag == true)
	{
		DrawMesh(&mesh, color);
	}
	else
	{
		DrawMesh(&mesh);
	}
}

D3DXVECTOR3 Enemy::GetPos(void)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

D3DXMATRIX Enemy::GetMat(void)
{
	return mat;
}

XFILE Enemy::GetMesh(void)
{
	return mesh;
}

void Enemy::GetCollisionSphere(CollisionSphere * CollisionSphereA, CollisionSphere * CollisionSphereB)
{
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2, mat._43);		//Y座標要調整☆	
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 5, mat._43);
	CollisionSphereA->radius = 3;		//変数化☆
	CollisionSphereB->radius = 3;
}

D3DXVECTOR3 Enemy::CheckOverlapEnemies(D3DXVECTOR3 *TargetPos)
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
	else
	{
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

bool Enemy::TakeDamage(int Damage)
{
	damageFlag = true;
	damageEffectCnt = 10;	//10フレーム
	HP -= Damage;
	if (HP <= 0)
	{
		return false;
	}
	return true;
}
