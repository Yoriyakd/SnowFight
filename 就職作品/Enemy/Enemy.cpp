#include "Enemy.h"
#include"EnemyState/EngagingMode.h"

const int Enemy::DEFAULT_HP = 3;
const float Enemy::HAT_RADIUS = 1.0f;
const float Enemy::HAT_HIGHT = 2.0f;
const float Enemy::SPHERE_RADIUS_HEAD = 1.3f;
const float Enemy::SPHER_RADIUS_BODY = 2.0f;
const float Enemy::SENSING_LENGTH = 60.0f;

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos) : nowState(new PlayerSearchState())
{
	bodyMesh = GetResource.GetXFILE(EnemyBody_M);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	handMesh = GetResource.GetXFILE(EnemyHand_M);

	hatMesh = GetResource.GetXFILE(EnemyHat_M);
	D3DXMatrixTranslation(&hatOffsetMat, 0.0f, 6.6f, -0.3f);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//生まれたときランダムな角度に (かまくらから生まれるときはこれじゃダメだから変える
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	D3DXMatrixRotationX(&hatRotMat, D3DXToRadian(-10));

	hatMat = hatRotMat * hatOffsetMat * mat;

	nowHP = DEFAULT_HP;
}

Enemy::~Enemy()
{
	delete nowState;
}

bool Enemy::Update(SnowBallManager & SnowBallManager, StageBorder & StageBorder)
{
	moveVec.y -= 0.005f;

	D3DXMATRIX MoveMat;
	D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);


	mat = MoveMat * mat;

	if (mat._42 < 0.0f)
	{
		mat._42 = 0.0f;
		moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	StageBorderProcessing(StageBorder);			//移動処理のあとに呼ぶ

	hatMat = hatRotMat * hatOffsetMat * mat;

	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&bodyMesh);
	
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&handMesh);

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
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2.0f, mat._43);
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 4.7f, mat._43);
	CollisionSphereA->radius = SPHERE_RADIUS_HEAD;
	CollisionSphereB->radius = SPHER_RADIUS_BODY;
}

float Enemy::GetRadisu(void)
{
	return SPHER_RADIUS_BODY;
}

bool Enemy::IsJump()
{
	if (mat._42 > 0.0f){ return true;}
	return false;
}

D3DXVECTOR3 Enemy::GetPlayerVec()
{
	return GetPlayer.GetPlayerPos() - D3DXVECTOR3(mat._41, mat._42, mat._43);
}

D3DXVECTOR3 Enemy::GetPlayerVec(D3DXVECTOR3 &Pos)
{
	return GetPlayer.GetPlayerPos() - Pos;
}

float Enemy::GetToPlayerAng()
{
	D3DXVECTOR3 TragetVec, DefaultVec(0, 0, 1);

	TragetVec = GetPlayerVec();

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
	return TragetAng;
}

float Enemy::GetToPlayerAng(D3DXVECTOR3 &Offset)
{
	D3DXVECTOR3 TragetVec, DefaultVec(0, 0, 1);

	TragetVec = GetPlayerVec(Offset);

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
	return TragetAng;
}

void Enemy::SetMat(D3DXMATRIX& _Mat)
{
	mat = _Mat;
}

void Enemy::PushedObj(const D3DXVECTOR3 &PushVec)
{
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, PushVec.x, PushVec.y, PushVec.z);

	mat = mat * TmpMat;
}

D3DXMATRIX Enemy::GetHatMat(void)
{
	return hatMat;
}

float Enemy::GetHatRadius(void)
{
	return HAT_RADIUS;
}

float Enemy::GetHatHight(void)
{
	return HAT_HIGHT;
}

float Enemy::GetSensingLength(void)
{
	return SENSING_LENGTH;
}

float Enemy::CalculateEnemyToPlayerAng()
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
	float TragetAng;

	TragetAng = GetToPlayerAng();

	//------------------------------------------------------
	//角度の差を求める
	//------------------------------------------------------

	float Ang;

	Ang = TragetAng - NowAng;							//初期の角度と今の角度の差を求める

	if (Ang > 180)			//鋭角への変換
	{
		Ang -= 360;
	}

	if (Ang < -180)
	{
		Ang += 360;
	}

	return Ang;
}

void Enemy::Spin(float AtOneceAng)
{
	if (IsJump() == false)
	{
		Jump();
	}
	D3DXMATRIX TmpRotMat;

	D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(AtOneceAng));

	mat = TmpRotMat * mat;
}

void Enemy::Jump(void)
{
	if (IsJump())return;
	D3DXVECTOR3 JumpVec(0.0f, 0.05f, 0.0f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
}

void Enemy::FrontJump(void)
{
	if (IsJump())return;
	D3DXVECTOR3 JumpVec(0.0f, 0.1f, 0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
}

void Enemy::BackJump(void)
{
	if (IsJump())return;
	D3DXVECTOR3 JumpVec(0.0f, 0.05f, -0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
}

void Enemy::ShootSnowBall()
{
	D3DXVECTOR3 OffsetTmp(3, 3, 0);
	ThrowingInitValue ValueTmp;

	D3DXVec3TransformCoord(&OffsetTmp, &OffsetTmp, &mat);

	ValueTmp.shootPos = OffsetTmp;
	ValueTmp.YAxisAng = GetToPlayerAng(OffsetTmp);						/*要調整☆*/
	ValueTmp.XAxisAng = 30;								/*要調整*/	//☆
	ValueTmp.powerRate = 45.0f + rand() % 5;							/*要調整*/

	GetSnowBallManager.SetSnowBall(&ValueTmp, ENEMY_ID);
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
	nowState = new EngagingMode();
	nowHP -= Damage;
	if (nowHP <= 0)
	{
		return false;
	}
	return true;
}


//=====================================
//privateメソッド
//=====================================


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
