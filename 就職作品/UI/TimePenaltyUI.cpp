#include "TimePenaltyUI.h"

TimePenaltyUI::TimePenaltyUI(int _MinusTime)
{
	minusTex = GetResource.GetTexture(TimePenalty_Tex);
	numberTex = GetResource.GetTexture(TimeNumber_Tex);

	D3DXMatrixTranslation(&numberOffsetMat, 56, 0, 0);
	D3DXMatrixTranslation(&mat, 100, 80, 0);
	displayTime_s = _MinusTime;
}

TimePenaltyUI::~TimePenaltyUI()
{
}

void TimePenaltyUI::Draw()
{

	RECT RcMinus = { 0, 0, 46, 46 };
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(minusTex, &RcMinus, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));


	int DisplayNum;
	const int NUM_DIGITS = 4;		//末尾に\0が挿入されるため3桁表示する際4をいれる
	char cTime[NUM_DIGITS];
	D3DXMATRIX NumberMat, NumberDisMat;

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//文字の間隔

	NumberMat = mat * numberOffsetMat;

	sprintf_s(cTime, sizeof(cTime), "%d", displayTime_s);		//1桁ずつ取り出せるように文字に変換


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
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0, -0.5f, 0);
	mat = Tmp * mat;
	alpha--;
	if (alpha < 0)
	{
		return false;
	}
	return true;
}	
