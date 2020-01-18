#include "Enemy.h"
#include"EnemyState/EngagingMode.h"

//=====================================
//public���\�b�h
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos) : jumpState(false), nowState(new PlayerSearchState())
{
	bodyMesh = GetResource.GetXFILE(EnemyBody_M);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	handMesh = GetResource.GetXFILE(EnemyHand_M);

	hatMesh = GetResource.GetXFILE(EnemyHat_M);
	D3DXMatrixTranslation(&hatOffsetMat, 0.0f, 6.6f, -0.3f);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//���܂ꂽ�Ƃ������_���Ȋp�x�� (���܂��炩�琶�܂��Ƃ��͂��ꂶ��_��������ς���
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	D3DXMatrixRotationX(&hatRotMat, D3DXToRadian(-10));

	hatMat = hatRotMat * hatOffsetMat * mat;

	HP = 3;
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
		jumpState = false;
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

	StageBorderProcessing(StageBorder);			//�ړ������̂��ƂɌĂ�

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
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2.0f, mat._43);		//Y���W�v������	
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 4.7f, mat._43);
	CollisionSphereA->radius = SphereRadiusHead;
	CollisionSphereB->radius = SphereRadiusBody;
}

bool Enemy::GetJumpState()
{
	return jumpState;
}

D3DXVECTOR3 Enemy::GetPlayerVec()
{
	return GetPlayer.GetPlayerPos() - D3DXVECTOR3(mat._41, mat._42, mat._43);
}

float Enemy::GetToPlayerAng()
{
	D3DXVECTOR3 TragetVec, DefaultVec(0, 0, 1);

	TragetVec = GetPlayerVec();

	D3DXVec3Normalize(&TragetVec, &TragetVec);				//�x�N�g�����K��

	float TragetDot;

	TragetDot = D3DXVec3Dot(&TragetVec, &DefaultVec);		//�����x�N�g���ƃv���C���[�ւ̃x�N�g��������ς����߂�

	if (TragetDot > 1)TragetDot = 1;						//���ς̒l��1���傫���Ȃ�Ȃ��悤��
	if (TragetDot < -1)TragetDot = -1;						//���ς̒l��-1��菬�������Ȃ�Ȃ��悤��

	float TragetAng;

	TragetAng = D3DXToDegree(acos(TragetDot));				//�v���C���[�Ə����̊p�x�����߂�

	if (TragetVec.x < 0)									//�p�x�̐����`�F�b�N	(�O�ς��g��Ȃ����@�ŋ��߂Ă���)
	{
		TragetAng *= -1;
	}
	return TragetAng;
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
	return hatRadius;
}

float Enemy::GetHatHight(void)
{
	return hatHight;
}

float Enemy::CalculateEnemyToPlayerAng()
{
	//------------------------------------------------------
	//���݂̊p�x�����߂�
	//------------------------------------------------------

	D3DXVECTOR3 NowFrontVec, DefaultVec(0, 0, 1);

	D3DXVec3TransformNormal(&NowFrontVec, &DefaultVec, &mat);	//���݂̕����x�N�g�������߂�

	D3DXVec3Normalize(&NowFrontVec, &NowFrontVec);				//�����x�N�g�����K��

	float NowDot;

	NowDot = D3DXVec3Dot(&NowFrontVec, &DefaultVec);			//�����x�N�g���ƌ��݂̕����x�N�g���œ��ς����ߌ��݂̊p�x�����߂�

	if (NowDot > 1)NowDot = 1;									//���ς̒l��1���傫���Ȃ�Ȃ��悤��
	if (NowDot < -1)NowDot = -1;								//���ς̒l��-1��菬�������Ȃ�Ȃ��悤��

	float NowAng;

	NowAng = D3DXToDegree(acos(NowDot));


	if (NowFrontVec.x < 0)			//�p�x�̐����`�F�b�N	(�O�ς��g��Ȃ����@�ŋ��߂Ă���)
	{
		NowAng *= -1;
	}

	//------------------------------------------------------
	//�v���C���[�Ƃ̊p�x�����߂�
	//------------------------------------------------------
	float TragetAng;

	TragetAng = GetToPlayerAng();

	//------------------------------------------------------
	//�p�x�̍������߂�
	//------------------------------------------------------

	float Ang;

	Ang = TragetAng - NowAng;							//�����̊p�x�ƍ��̊p�x�̍������߂�

	if (Ang > 180)			//�s�p�ւ̕ϊ�
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
	if (jumpState == false)
	{
		Jump();
	}
	D3DXMATRIX TmpRotMat;

	D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(AtOneceAng));

	mat = TmpRotMat * mat;
}

void Enemy::Jump(void)
{
	if (jumpState == true)return;
	D3DXVECTOR3 JumpVec(0.0f, 0.05f, 0.0f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
	jumpState = true;
}

void Enemy::FrontJump(void)
{
	if (jumpState == true)return;
	D3DXVECTOR3 JumpVec(0.0f, 0.1f, 0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
	jumpState = true;
}

void Enemy::BackJump(void)
{
	if (jumpState == true)return;
	D3DXVECTOR3 JumpVec(0.0f, 0.05f, -0.1f);
	D3DXMATRIX TmpMat;

	moveVec = JumpVec;
	jumpState = true;
}

void Enemy::ShootSnowBall()
{
	D3DXVECTOR3 PosTmp(3, 3, 0);
	D3DXVec3TransformCoord(&PosTmp, &PosTmp, &mat);

	ThrowingInitValue ValueTmp;
	ValueTmp.shootPos = PosTmp;

	ValueTmp.XAxisAng = 30;								/*�v����*/	//��
	ValueTmp.YAxisAng = GetToPlayerAng() - 5;						/*�v�����肩�甭�˂��邽�߂̉��}���u��*/
	ValueTmp.powerRate = 40.0f;							/*�v����*/

	GetSnowBallManager.SetSnowBall(&ValueTmp, ENEMY_ID);
}

void Enemy::CheckOverlapEnemies(const D3DXVECTOR3 *TargetPos)
{

	D3DXVECTOR3 TargetVec;

	TargetVec = D3DXVECTOR3(mat._41, 0.0f, mat._43) - D3DXVECTOR3(TargetPos->x, 0.0f, TargetPos->z);		//Y���W�𖳎�����

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	float Radius = 3;	//�ϐ���
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
	HP -= Damage;
	if (HP <= 0)
	{
		return false;
	}
	return true;
}


//=====================================
//private���\�b�h
//=====================================


void Enemy::StageBorderProcessing(StageBorder & StageBorder)
{
	//�X�e�[�W���E�̏���
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
