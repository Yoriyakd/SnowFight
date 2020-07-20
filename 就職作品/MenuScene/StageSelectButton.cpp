#include "StageSelectButton.h"
#include"../DirectX/Sprite.h"

StageSelectButton::StageSelectButton() : onMouseColor(200)
{
	D3DXMatrixTranslation(&textOffsetMat, 4, 95, 0);
	D3DXMatrixTranslation(&numOffsetMat, 90, 95, 0);
	D3DXMatrixTranslation(&picOffsetMat, 18, 30, 0);
}

StageSelectButton::~StageSelectButton()
{
}

void StageSelectButton::Draw()
{
	RECT RcBack = { 0, 0, 132, 132 };
	Sprite::GetInstance().GetSprite()->SetTransform(&mat);
	Sprite::GetInstance().GetSprite()->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

	D3DXMATRIX TmpMat;

	TmpMat = picOffsetMat * mat;

	RECT RcPic = { 0, 0, 96, 54 };
	Sprite::GetInstance().GetSprite()->SetTransform(&TmpMat);
	Sprite::GetInstance().GetSprite()->Draw(stagePicTex, &RcPic, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

	RECT RcText = { 0, 0, 132, 30 };

	TmpMat = textOffsetMat * mat;
	Sprite::GetInstance().GetSprite()->SetTransform(&TmpMat);
	Sprite::GetInstance().GetSprite()->Draw(stageTextTex, &RcText, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, onMouseColor, onMouseColor, onMouseColor));

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

		Sprite::GetInstance().GetSprite()->SetTransform(&NumberMat);
		Sprite::GetInstance().GetSprite()->Draw(stageNumTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//右にずらす
	}
}

void StageSelectButton::OnMouseEvent(void)
{
	onMouseColor = 200;
}

void StageSelectButton::OffMouseEvent(void)
{
	onMouseColor = 255;
}

void StageSelectButton::Stage1Initialize(void)
{
	stageNum = 1;
	stagePicTex = GetResource.GetTexture(Stage1Button_Tex);
	stageTextTex = GetResource.GetTexture(ButtonText_Tex);
	backTex = GetResource.GetTexture(ButtonBack_Tex);
	stageNumTex = GetResource.GetTexture(ButtonNum_Tex);
	buttonData.Pos = D3DXVECTOR2(480, 190);
	buttonData.BoxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, buttonData.Pos.x, buttonData.Pos.y, 0);
}

void StageSelectButton::Stage2Initialize(void)
{
	stageNum = 2;
	stagePicTex = GetResource.GetTexture(Stage2Button_Tex);
	stageTextTex = GetResource.GetTexture(ButtonText_Tex);
	backTex = GetResource.GetTexture(ButtonBack_Tex);
	stageNumTex = GetResource.GetTexture(ButtonNum_Tex);
	buttonData.Pos = D3DXVECTOR2(620, 190);
	buttonData.BoxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, buttonData.Pos.x, buttonData.Pos.y, 0);
}
