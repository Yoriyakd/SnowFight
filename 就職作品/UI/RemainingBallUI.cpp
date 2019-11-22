#include "RemainingBallUI.h"

RemainingBallUI::RemainingBallUI()
{
	backTex = resourceManager->GetTexture("SnowBallUI.png", 256, 64, NULL);
	numberTex = resourceManager->GetTexture("Number.png", 420, 42, NULL);

	D3DXMatrixTranslation(&backMat, 500, 0, 0);
	D3DXMatrixTranslation(&numberOffsetMat, 120.0f, 15.0f, 0);
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
	RECT RcPickUpInstructions = { 0, 0, 256, 64 };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcPickUpInstructions, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	int DisplayNum;
	const int NUM_DIGITS = 4;		//––”ö‚É\0‚ª‘}“ü‚³‚ê‚é‚½‚ß3Œ…•\¦‚·‚éÛ4‚ğ‚¢‚ê‚é
	char cBallCnt[NUM_DIGITS];
	D3DXMATRIX NumberMat, NumberDisMat;

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//•¶š‚ÌŠÔŠu

	NumberMat = backMat * numberOffsetMat;

	sprintf_s(cBallCnt, sizeof(cBallCnt), "%d", displayBallCnt);		//1Œ…‚¸‚Âæ‚èo‚¹‚é‚æ‚¤‚É•¶š‚É•ÏŠ·

	for (int i = 0; i < NUM_DIGITS; i++)
	{
		DisplayNum = cBallCnt[i] - '0';		//”š‚É•ÏŠ·

		RECT RcNumber = { 42 * DisplayNum, 0, 42 * (DisplayNum + 1), 42 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//‰E‚É‚¸‚ç‚·
	}
}