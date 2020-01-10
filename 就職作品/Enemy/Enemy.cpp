#include "Enemy.h"
#include"../GameScene/GameScene.h"//��

//=====================================
//public���\�b�h
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos) : jumpState(false), nowState(new PlayerSearchState())
{
	bodyMesh = GetResource.GetXFILE(EnemyBody_M);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	hatMesh = GetResource.GetXFILE(EnemyHat_M);
	D3DXMatrixTranslation(&hatOffsetMat, 0.0f, 6.6f, -0.3f);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//���܂ꂽ�Ƃ������_���Ȋp�x�� (���܂��炩�琶�܂��Ƃ��͂��ꂶ��_��������ς���
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	D3DXMatrixRotationX(&hatRotMat, D3DXToRadian(-10));

	hatMat = hatRotMat * hatOffsetMat * mat;

	MoveInterval = 0;	//�����l��0(��������)
	freeMoveCnt = (float)(rand() % 3) * GameFPS;	//������
	limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//minLength~maxLength�̊Ԃŏ�����	�ő�l��maxLength�ɂȂ�悤��+1���Ă���

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
	//TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�

	//float TragetLength, LimitLength = 50.0f;
	//TragetLength = D3DXVec3Length(&TragetVec);		//�v���C���[�Ƃ̋��������߂�

	//if (TragetLength < LimitLength)		//������LimitLength�����Ȃ���Mode�ɂȂ�
	//{
	//	EngagingMode(TragetPos ,SnowBallManager);
	//}
	//else
	//{
	//	FreeMode();						//�͈͊O�ő��ǐՏI���͕ς�����
	//}

	StageBorderProcessing(StageBorder);			//�ړ������̂��ƂɌĂ�

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
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2.0f, mat._43);		//Y���W�v������	
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
	//damageFlag = true;
	//damageEffectCnt = 10;	//10�t���[��
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

void Enemy::ShootSnowBall(const float TragetAng, SnowBallManager &snowBallManager)
{
	D3DXVECTOR3 PosTmp(3, 3, 0);
	D3DXVec3TransformCoord(&PosTmp, &PosTmp, &mat);

	ThrowingInitValue ValueTmp;
	ValueTmp.shootPos = PosTmp;
	
	ValueTmp.XAxisAng = 30;								/*�v����*/	//��
	ValueTmp.YAxisAng = TragetAng;						/*�v����*/
	ValueTmp.powerRate = 40.0f;							/*�v����*/


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

	D3DXVECTOR3 TragetVec;


	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�

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


	//------------------------------------------------------
	//�p�x�̍������߂�
	//------------------------------------------------------

	float MoveAng;

	MoveAng = TragetAng - NowAng;							//�����̊p�x�ƍ��̊p�x�̍������߂�

	if (MoveAng > 180)			//�s�p�ւ̕ϊ�
	{
		MoveAng -= 360;
	}

	if (MoveAng < -180)
	{
		MoveAng += 360;
	}

	//---------------------------------------------------
	//�K�v��]�ʂ����̉�]�ʂ�菬�����ꍇ��]�������Ȃ��悤�ɂ���
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
	//�ړ�����
	//---------------------------------------------------

	D3DXMATRIX MoveMat;

	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�	��Ő��K�����Ă��܂��Ă���̂ł�����x���߂�

	float TragetLength;

	if (rand() % 1000 < 1)		//0.1%�̊m���ōĒ��I
	{
		limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//�ő�l��maxLength�ɂȂ�悤�� + 1���Ă���
	}

	TragetLength = D3DXVec3Length(&TragetVec);		//�v���C���[�Ƃ̋��������߂�


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
	static const int MaxInterval = 10;			//�Ԋu�̍ő�l
	static const int MinInterval = 5;			//�Ԋu�̍ŏ��l

	if (MoveInterval < 0)
	{

		D3DXMatrixTranslation(&MoveMat, 0.0f, 0.0f, 0.2f);
		mat = MoveMat * mat;
		freeMoveCnt--;
		if (freeMoveCnt < 0)				//�K��̎��ԓ������玟�����܂ł̎��Ԃ��Đݒ�
		{
			MoveInterval = (float)(rand() % (MaxInterval + 1 - MinInterval) + MinInterval) * GameFPS;			//�����_���Ŏ������܂ł̎��Ԃ����߂�	�ő�l��MaxInterval�ɂȂ�悤��+1���Ă���
			freeMoveCnt = (float)(rand() % 3) * GameFPS;
		}
	}

	MoveInterval--;

}

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
