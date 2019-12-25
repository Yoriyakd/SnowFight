#include "GameObjective.h"

GameObjective::GameObjective()
{
	backTex = GetResource.GetTexture("GameObjective.png", 400, 64, NULL);
	D3DXMatrixTranslation(&backMat, 800.0f, 10.0f, 0.0f);

	numberTex = GetResource.GetTexture("Number.png", 420, 42, NULL);
	D3DXMatrixTranslation(&numberOffsetMat, 290.0f, 15.0f, 0.0f);

	clearTex = GetResource.GetTexture("Clear.png", 400, 64, NULL);
}

GameObjective::~GameObjective()
{
}

void GameObjective::SetNorm(int Norm)
{
	normCnt = Norm;
}

void GameObjective::SetNowNormCnt(int NowCnt)
{
	nowCnt = NowCnt;
}

void GameObjective::SetNormState(bool NormState)
{
	normState = NormState;
}

void GameObjective::Draw()
{
	if (normState == false)		//ノルマ未達成なら
	{
		RECT RcBack = { 0, 0, 400, 64 };
		lpSprite->SetTransform(&backMat);
		lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		D3DXMATRIX NumberMat, NumberDisMat;

		NumberMat = backMat * numberOffsetMat;		//文字の表示行列


		RECT RcNow = { 42 * nowCnt, 0, 42 * (nowCnt + 1), 42 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNow, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		D3DXMatrixTranslation(&NumberDisMat, 60, 0, 0);			//文字の間隔
		NumberMat = NumberDisMat * NumberMat;			//右にずらす

		RECT RcNorm = { 42 * normCnt, 0, 42 * (normCnt + 1), 42 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNorm, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else                   //ノルマ達成なら
	{
		RECT RcClear = { 0, 0, 400, 64 };
		lpSprite->SetTransform(&backMat);
		lpSprite->Draw(clearTex, &RcClear, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}
