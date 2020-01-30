#include "ButtonBase.h"

ButtonBase::ButtonBase(int No):onMouseColor(200)
{
	switch (No)
	{
	case 1:
		Stage1Initialize();
		break;
	case 2:
		Stage2Initialize();
	default:
		break;
	}

	D3DXMatrixTranslation(&textOffsetMat, 4, 95, 0);
	D3DXMatrixTranslation(&numOffsetMat, 90, 95, 0);
	D3DXMatrixTranslation(&picOffsetMat, 18, 30, 0);
	stageNum = No;
}

void ButtonBase::Draw()
{
	RECT RcBack = { 0, 0, 132, 132};
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

	D3DXMATRIX TmpMat;

	TmpMat = picOffsetMat * mat;

	RECT RcPic = { 0, 0, 96, 54 };
	lpSprite->SetTransform(&TmpMat);
	lpSprite->Draw(stagePicTex, &RcPic, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

	RECT RcText = { 0, 0, 132, 30 };

	TmpMat = textOffsetMat * mat;
	lpSprite->SetTransform(&TmpMat);
	lpSprite->Draw(stageTextTex, &RcText, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

	int DisplayNum;
	D3DXMATRIX NumberMat, NumberDisMat;
	const int NUM_DIGITS = 4;		//末尾に\0が挿入されるため3桁表示する際4をいれる
	char cTime[NUM_DIGITS];

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//文字の間隔

	NumberMat = numOffsetMat * mat;

	sprintf_s(cTime, sizeof(cTime), "%d", stageNum);		//1桁ずつ取り出せるように文字に変換

	for (int i = 0; i < NUM_DIGITS; i++)
	{
		if (cTime[i] == '\0')break;		//要素の終端ならbreak

		DisplayNum = cTime[i] - '0';		//数字に変換

		RECT RcNumber = { 30 * DisplayNum, 0, 30 * (DisplayNum + 1), 30 };

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(stageNumTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//右にずらす
	}
}

void ButtonBase::Update()
{
	POINT Pt;

	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	ScreenToClient(hwnd, &Pt);		//スクリーン座標に変換

	if (Pt.x >= pos.x && Pt.x <= (pos.x + boxSize.x) &&		//矩形と点の当たり判定
		Pt.y >= pos.y && Pt.y <= (pos.y + boxSize.y))
	{
		nowStae = true;
		onMouseColor = 200;
	}
	else
	{
		nowStae = false;
		onMouseColor = 255;
	}
}

bool ButtonBase::GetState(void)
{
	return nowStae;
}

void ButtonBase::Stage1Initialize(void)
{
	stagePicTex = GetResource.GetTexture(Stage1Button_Tex);
	stageTextTex = GetResource.GetTexture(ButtonText_Tex);
	backTex = GetResource.GetTexture(ButtonBack_Tex);
	stageNumTex = GetResource.GetTexture(ButtonNum_Tex);
	pos = D3DXVECTOR2(480, 190);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}

void ButtonBase::Stage2Initialize(void)
{
	stagePicTex = GetResource.GetTexture(Stage2Button_Tex);
	stageTextTex = GetResource.GetTexture(ButtonText_Tex);
	backTex = GetResource.GetTexture(ButtonBack_Tex);
	stageNumTex = GetResource.GetTexture(ButtonNum_Tex);
	pos = D3DXVECTOR2(620, 190);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}
