#include "RemainingBallUI.h"

RemainingBallUI::RemainingBallUI()
{
	backTex = resourceManager->GetTexture("SnowBallUI.png", 256, 64, NULL);
	D3DXMatrixTranslation(&backMat, 500, 10, 0);

	numberTex = resourceManager->GetTexture("Number.png", 420, 42, NULL);
	D3DXMatrixTranslation(&numberOffsetMat, 120.0f, 13.0f, 0);
}

RemainingBallUI::~RemainingBallUI()
{
}

void RemainingBallUI::SetRemainingBallCnt(int Cnt)
{
	displayBallCnt = Cnt;
}

void RemainingBallUI::Draw()
{
	RECT RcBack = { 0, 0, 256, 64 };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	int DisplayNum;
	const int NUM_DIGITS = 4;		//末尾に\0が挿入されるため3桁表示する際4をいれる
	char cBallCnt[NUM_DIGITS];
	D3DXMATRIX NumberMat, NumberDisMat;

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//文字の間隔

	NumberMat = backMat * numberOffsetMat;

	sprintf_s(cBallCnt, sizeof(cBallCnt), "%d", displayBallCnt);		//1桁ずつ取り出せるように文字に変換

	for (int i = 0; i < NUM_DIGITS; i++)
	{
		if (cBallCnt[i] == '\0')break;		//要素の終端ならbreak

		DisplayNum = cBallCnt[i] - '0';		//数字に変換

		RECT RcNumber = { 42 * DisplayNum, 0, 42 * (DisplayNum + 1), 42 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//右にずらす
	}
}