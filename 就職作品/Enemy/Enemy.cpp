#include "Enemy.h"
#include"../GameScene/GameScene.h"


//=====================================
//private���\�b�h
//=====================================

void Enemy::ShootSnowBall(float TragetAng)
{
	SnowBallInitValue ValueTmp;
	ValueTmp.shootPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	ValueTmp.shootPos.y += 3;							//���ˈʒu����(�ϐ���)	��̈ʒu���甭�˂���悤�ɂ���
	ValueTmp.XAxisAng = 30;								/*�v����*/	//��
	ValueTmp.YAxisAng = TragetAng;						/*�v����*/
	ValueTmp.powerRate = 20.0f;							/*�v����*/
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

	D3DXVECTOR3 TragetVec, TragetPos;

	TragetPos = player->GetPlayerPos();

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

	ShootSnowBall(TragetAng);
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

void Enemy::StageBorderProcessing(void)
{
	//�X�e�[�W���E�̏���
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
//public���\�b�h
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("EnemyBody.x");
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&transMat, Pos.x, Pos.y, Pos.z);

	D3DXMATRIX InitRotMat;
	float TmpRndAng;

	TmpRndAng = (float)(rand() % 360);		//���܂ꂽ�Ƃ������_���Ȋp�x�� (���܂��炩�琶�܂��Ƃ��͂��ꂶ��_��������ς���
	D3DXMatrixRotationY(&InitRotMat ,D3DXToRadian(TmpRndAng));

	mat = InitRotMat * transMat;

	MoveInterval = 0;	//�����l��0(��������)
	freeMoveCnt = (float)(rand() % 3) * GameFPS;	//������
	limitLength = rand() % (int)(maxLength + 1 - minLength) + minLength;		//minLength~maxLength�̊Ԃŏ�����	�ő�l��maxLength�ɂȂ�悤��+1���Ă���

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
	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�

	float TragetLength, LimitLength = 50.0f;
	TragetLength = D3DXVec3Length(&TragetVec);		//�v���C���[�Ƃ̋��������߂�

	if (TragetLength < LimitLength)		//������LimitLength�����Ȃ���Mode�ɂȂ�
	{
		EngagingMode();
	}
	else
	{
		FreeMode();						//�͈͊O�ő��ǐՏI���͕ς�����
	}

	StageBorderProcessing();			//�ړ������̂��ƂɌĂ�

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
	
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2, mat._43);		//Y���W�v������	
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 5, mat._43);
	CollisionSphereA->radius = 3;		//�ϐ�����
	CollisionSphereB->radius = 3;
}

D3DXVECTOR3 Enemy::CheckOverlapEnemies(D3DXVECTOR3 *TargetPos)
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
	else
	{
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

bool Enemy::TakeDamage(int Damage)
{
	damageFlag = true;
	damageEffectCnt = 10;	//10�t���[��
	HP -= Damage;
	if (HP <= 0)
	{
		return false;
	}
	return true;
}
