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
	InitPos();			//表示するたびに座標を変える
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
	if (displayCnt <= 0)			//規定時間表示したのち薄くし始める
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
	PlayerVecTmp.y = 0.0f;				//Y方向の情報は必要ない
	D3DXVec3Normalize(&PlayerVecTmp, &PlayerVecTmp);

	SnowBallVecTmp = SnowBallVec;
	SnowBallVecTmp.y = 0.0f;			//Y方向の情報は必要ない

	D3DXVec3Normalize(&SnowBallVecTmp, &SnowBallVecTmp);

	float Dot;
	Dot = D3DXVec3Dot(&PlayerVecTmp, &-SnowBallVecTmp);			//playerの方に向かうベクトルのため雪玉のベクトルは反転させたものを使う

	if (Dot > 1)Dot = 1;						//内積の値が1より大きくならないように
	if (Dot < -1)Dot = -1;						//内積の値が-1より小さくくならないように

	if (Dot < 0)		//内積が負の値なら後ろから
	{
		return Back;
	}

	D3DXVECTOR3 CrossTmp;

	D3DXVec3Cross(&CrossTmp, &PlayerVecTmp, &SnowBallVecTmp);
	if (CrossTmp.y > 0)			//外積で得たベクトルが上向きなら左からHIT
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
