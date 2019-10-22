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
	ValueTmp.XAxisAng = 30;								/*要調整*/
	ValueTmp.YAxisAng = TragetAng;						/*要調整*/
	ValueTmp.powerRate = 20.0f;							/*要調整*/
	ValueTmp.id = ENEMY_ID;

	static int CoolTime = 3 * GameFPS;					//雪玉発射のクールタイム※要調整
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

	D3DXVec3Cross(&RotAxis, &DefaultVec, &TragetVec);		//外積を求める

	if (RotAxis.y < 0)										//外積の方向が負なら
	{
		TragetAng *= -1;									//角度は負(反時計回り)
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

	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//プレイヤーへのベクトルを求める	上で正規化仕手しまっているのでもう一度求める

	float TragetLength, LimitLength = 30.0f;
	TragetLength = D3DXVec3Length(&TragetVec);		//プレイヤーとの距離を求める

	if (TragetLength < LimitLength)
	{
		D3DXMatrixTranslation(&MoveMat, 0, 0, -0.2);
	}
	else
	{
		D3DXMatrixTranslation(&MoveMat, 0.1, 0, 0.2);		//右に移動するようにしてみた理由は特にない
	}
	
	mat = MoveMat * mat;

	ShootSnowBall(TragetAng);
}

void Enemy::FreeMode(void)
{
	D3DXMATRIX MoveMat;
	static float MoveInterval = 0;		//動くまでの時間初期値は0		//静的変数にするとすべてのインスタンスで共有されてしまう？上のクールタイムはそうではなさそうだが
	static const int MaxInterval = 21;			//間隔の最大値
	static const int MinInterval = 5;			//間隔の最大値

	if (MoveInterval < 0)
	{
		static float MoveCnt = 3 * GameFPS;
		D3DXMatrixTranslation(&MoveMat, 0.0, 0, 0.2);
		mat = MoveMat * mat;
		MoveCnt--;
		if (MoveCnt < 0)				//規定の時間動いたら次動くまでの時間を再設定
		{
			MoveInterval = (rand() % (MaxInterval + MinInterval) + MinInterval) * GameFPS;			//ランダムで次動くまでの時間を決める
			MoveCnt = 3 * GameFPS;
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
	mesh = resourceManager->GetXFILE("Enemy/EnemyBody.x");
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = rand() % 360;
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * mat;
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
	else
	{
		FreeMode();						//範囲外で即追跡終了は変えたい
	}

	StageBorderProcessing();			//移動処理のあとに呼ぶ
	
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
