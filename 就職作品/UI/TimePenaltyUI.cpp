#include "TimePenaltyUI.h"

TimePenaltyUI::TimePenaltyUI(int _MinusTime) : effectDisplayFlag(-1), flashIntervalCnt(0) , penaltyTime_s(_MinusTime), displayTime_frame(90)
{
	minusTex = GetResource.GetTexture(TimePenalty_Tex);
	numberTex = GetResource.GetTexture(TimeNumber_Tex);
	effectTex = GetResource.GetTexture(TimePenaltyEffect_Tex);

	D3DXMatrixTranslation(&numberOffsetMat, 56, 0, 0);
	D3DXMatrixTranslation(&mat, 100, 60, 0);
	D3DXMatrixTranslation(&effectMat, -60, -30, 0);
}

TimePenaltyUI::~TimePenaltyUI()
{
}

void TimePenaltyUI::Draw()
{
	if (effectDisplayFlag == 1)
	{
		RECT RcEffect = { 0, 0, 256, 256 };
		lpSprite->SetTransform(&effectMat);
		lpSprite->Draw(effectTex, &RcEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	RECT RcMinus = { 0, 0, 46, 46 };
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(minusTex, &RcMinus, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));


	int DisplayNum;
	const int NUM_DIGITS = 4;		//末尾に\0が挿入されるため3桁表示する際4をいれる
	char cTime[NUM_DIGITS];
	D3DXMATRIX NumberMat, NumberDisMat;

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//文字の間隔

	NumberMat = mat * numberOffsetMat;

	sprintf_s(cTime, sizeof(cTime), "%d", penaltyTime_s);		//1桁ずつ取り出せるように文字に変換


	for (int i = 0; i < NUM_DIGITS; i++)
	{
		if (cTime[i] == '\0')break;		//要素の終端ならbreak

		DisplayNum = cTime[i] - '0';		//数字に変換

		RECT RcNumber = { 46 * DisplayNum, 0, 46 * (DisplayNum + 1), 46 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//右にずらす
	}

}

bool TimePenaltyUI::Update()
{
	displayTime_frame--;
	if (displayTime_frame > 0)
	{
		flashIntervalCnt--;
		if (flashIntervalCnt < 0)
		{
			effectDisplayFlag *= -1;
			flashIntervalCnt = EFFECT_FLASH_INTERVAL;
		}
		return true;		//表示時間が終わってから薄くなり始める
	}
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0, -0.3f, 0);
	mat = Tmp * mat;
	alpha -= 2;
	if (alpha < 0)
	{
		return false;
	}
	return true;
}	
