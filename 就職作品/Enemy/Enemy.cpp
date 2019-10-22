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
	ValueTmp.XAxisAng = 30;								/*�v����*/
	ValueTmp.YAxisAng = TragetAng;						/*�v����*/
	ValueTmp.powerRate = 20.0f;							/*�v����*/
	ValueTmp.id = ENEMY_ID;

	static int CoolTime = 3 * GameFPS;					//��ʔ��˂̃N�[���^�C�����v����
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

	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &DefaultVec, &NowFrontVec);			//�O�ς�����

	if (RotAxis.y < 0)											//�O�ς̕��������Ȃ�
	{
		NowAng *= -1;											//�p�x�͕�(�����v���)
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

	D3DXVec3Cross(&RotAxis, &DefaultVec, &TragetVec);		//�O�ς����߂�

	if (RotAxis.y < 0)										//�O�ς̕��������Ȃ�
	{
		TragetAng *= -1;									//�p�x�͕�(�����v���)
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

	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�	��Ő��K���d�肵�܂��Ă���̂ł�����x���߂�

	float TragetLength, LimitLength = 30.0f;
	TragetLength = D3DXVec3Length(&TragetVec);		//�v���C���[�Ƃ̋��������߂�

	if (TragetLength < LimitLength)
	{
		D3DXMatrixTranslation(&MoveMat, 0, 0, -0.2);
	}
	else
	{
		D3DXMatrixTranslation(&MoveMat, 0.1, 0, 0.2);		//�E�Ɉړ�����悤�ɂ��Ă݂����R�͓��ɂȂ�
	}
	
	mat = MoveMat * mat;

	ShootSnowBall(TragetAng);
}

void Enemy::FreeMode(void)
{
	D3DXMATRIX MoveMat;
	static float MoveInterval = 0;		//�����܂ł̎��ԏ����l��0		//�ÓI�ϐ��ɂ���Ƃ��ׂẴC���X�^���X�ŋ��L����Ă��܂��H��̃N�[���^�C���͂����ł͂Ȃ���������
	static const int MaxInterval = 21;			//�Ԋu�̍ő�l
	static const int MinInterval = 5;			//�Ԋu�̍ő�l

	if (MoveInterval < 0)
	{
		static float MoveCnt = 3 * GameFPS;
		D3DXMatrixTranslation(&MoveMat, 0.0, 0, 0.2);
		mat = MoveMat * mat;
		MoveCnt--;
		if (MoveCnt < 0)				//�K��̎��ԓ������玟�����܂ł̎��Ԃ��Đݒ�
		{
			MoveInterval = (rand() % (MaxInterval + MinInterval) + MinInterval) * GameFPS;			//�����_���Ŏ������܂ł̎��Ԃ����߂�
			MoveCnt = 3 * GameFPS;
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
	TragetVec = TragetPos - D3DXVECTOR3(mat._41, mat._42, mat._43);		//�v���C���[�ւ̃x�N�g�������߂�

	float TragetLength, LimitLength = 80.0f;
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
	
	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

}

D3DXVECTOR3 Enemy::GetPos(void)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

void Enemy::GetCollisionSphere(CollisionSphere * CollisionSphereA, CollisionSphere * CollisionSphereB)
{
	CollisionSphereA->pos = D3DXVECTOR3(mat._41, mat._42 + 2, mat._43);		//Y���W�v����
	CollisionSphereB->pos = D3DXVECTOR3(mat._41, mat._42 + 5, mat._43);
	CollisionSphereA->radius = 3;
	CollisionSphereB->radius = 3;
}
