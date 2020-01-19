#include "PlayerHitEffect.h"
#include"../Player/Player.h"

PlayerHitEffect::PlayerHitEffect()
{
	
}

PlayerHitEffect::~PlayerHitEffect()
{
}

void PlayerHitEffect::Initialize_BackEffect()
{
	tex = GetResource.GetTexture(BackHitEffect_Tex);
	id = Back;
	rect = RECT{ 0, 0, 1280, 720 };
}

void PlayerHitEffect::Initialize_RightEffect()
{
	tex = GetResource.GetTexture(HitEffect_Tex);
	id = Right;
	rect = RECT{0, 0, 500, 500};
}

void PlayerHitEffect::Initialize_LeftEffect()
{
	tex = GetResource.GetTexture(HitEffect_Tex);
	id = Left;
	rect = RECT{ 0, 0, 500, 500 };
}

void PlayerHitEffect::Active()
{
	activeFlag = true;
	alpha = 255;
	displayCnt = DISPLAY_TIME;
	InitPos();			//�\�����邽�тɍ��W��ς���
}

bool PlayerHitEffect::GetActiveState()
{
	return activeFlag;
}

void PlayerHitEffect::Draw()
{	
	if (activeFlag == false)return;
	lpSprite->SetTransform(&transMat);
	lpSprite->Draw(tex, &rect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

void PlayerHitEffect::Update()
{
	if (activeFlag == false)return;

	displayCnt--;
	if (displayCnt <= 0)			//�K�莞�ԕ\�������̂��������n�߂�
	{
		alpha -= 3;
		pos.y += 1;
	}
	
	if (alpha < 0)
	{
		activeFlag = false;
	}


	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
}

HitEffectID PlayerHitEffect::CalculateHitDirection(const D3DXVECTOR3 &SnowBallVec)
{
	D3DXVECTOR3 PlayerVecTmp(0, 0, 1), SnowBallVecTmp;

	D3DXVec3TransformNormal(&PlayerVecTmp, &PlayerVecTmp, &GetPlayer.GetMat());
	PlayerVecTmp.y = 0.0f;				//Y�����̏��͕K�v�Ȃ�
	D3DXVec3Normalize(&PlayerVecTmp, &PlayerVecTmp);

	SnowBallVecTmp = SnowBallVec;
	SnowBallVecTmp.y = 0.0f;			//Y�����̏��͕K�v�Ȃ�

	D3DXVec3Normalize(&SnowBallVecTmp, &SnowBallVecTmp);

	float Dot;
	Dot = D3DXVec3Dot(&PlayerVecTmp, &-SnowBallVecTmp);			//player�̕��Ɍ������x�N�g���̂��ߐ�ʂ̃x�N�g���͔��]���������̂��g��

	if (Dot > 1)Dot = 1;						//���ς̒l��1���傫���Ȃ�Ȃ��悤��
	if (Dot < -1)Dot = -1;						//���ς̒l��-1��菬�������Ȃ�Ȃ��悤��

	if (Dot < 0)		//���ς����̒l�Ȃ��납��
	{
		return Back;
	}

	D3DXVECTOR3 CrossTmp;

	D3DXVec3Cross(&CrossTmp, &PlayerVecTmp, &SnowBallVecTmp);
	if (CrossTmp.y > 0)			//�O�ςœ����x�N�g����������Ȃ獶����HIT
	{
		return Left;
	}
	else
	{
		return Right;
	}
}

void PlayerHitEffect::InitPos()
{
	switch (id)
	{
	case Right:
		pos = D3DXVECTOR3((float)(640 + (rand() % 140)), (float)(rand() % 220), 0);
		break;
	case Left:
		pos = D3DXVECTOR3((float)(rand() % 140), (float)(rand() % 220), 0);
		break;
	case Back:
		pos = D3DXVECTOR3(0, 0, 0);
		break;
	}
}
