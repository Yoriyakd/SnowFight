#include "TimeUI.h"
#include"../DirectX/Sprite.h"
#include"../DirectX/Sprite.h"

TimeUI::TimeUI()
{
	numberTex = GetResource.GetTexture(TimeNumber_Tex);
	D3DXMatrixTranslation(&numberOffsetMat, 10, 56, 0);

	logoTex = GetResource.GetTexture(TimeLogo_Tex);
	D3DXMatrixTranslation(&logoMat, 10, 10, 0);
}

TimeUI::~TimeUI()
{
}

void TimeUI::Draw()
{
	RECT RcLogo = { 0, 0, 194, 46 };
	Sprite::GetInstance().GetSprite()->SetTransform(&logoMat);
	Sprite::GetInstance().GetSprite()->Draw(logoTex, &RcLogo, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


	int DisplayNum;
	const int NUM_DIGITS = 4;		//������\0���}������邽��3���\�������4�������
	char cTime[NUM_DIGITS];
	D3DXMATRIX NumberMat, NumberDisMat;

	D3DXMatrixTranslation(&NumberDisMat, 40, 0, 0);			//�����̊Ԋu

	NumberMat = logoMat * numberOffsetMat;

	sprintf_s(cTime, sizeof(cTime), "%d", displayTime_s);		//1�������o����悤�ɕ����ɕϊ�
	

	for (int i = 0; i < NUM_DIGITS; i++)
	{
		if (cTime[i] == '\0')break;		//�v�f�̏I�[�Ȃ�break

		DisplayNum = cTime[i] - '0';		//�����ɕϊ�

		RECT RcNumber = { 46 * DisplayNum, 0, 46 * (DisplayNum + 1), 46 };

		Sprite::GetInstance().GetSprite()->SetTransform(&NumberMat);
		Sprite::GetInstance().GetSprite()->Draw(numberTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//�E�ɂ��炷
	}
	
	//�傫�������Ȃ��Ă��������\��
	for (auto BoldNumber : BoldNumber)
	{
		RECT RcBoldNumber = { 46 * BoldNumber->DisplayNum, 0, 46 * (BoldNumber->DisplayNum + 1), 46 };

		D3DXMATRIX TmpMat;

		TmpMat = BoldNumber->ScalMat * logoMat * numberOffsetMat;
		Sprite::GetInstance().GetSprite()->SetTransform(&TmpMat);
		//�����Ɍ������đ傫���Ȃ��Ă��炤����0, 0, 0������
		Sprite::GetInstance().GetSprite()->Draw(numberTex, &RcBoldNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(BoldNumber->Alpha, 255, 255, 255));
	}
}

void TimeUI::Update()
{
	for (unsigned int i = 0; i < BoldNumber.size(); i++)
	{
		D3DXMATRIX TmpScal;

		D3DXMatrixScaling(&TmpScal, 1.01f, 1.01f, 1.01f);

		BoldNumber[i]->ScalMat *= TmpScal;
		BoldNumber[i]->Alpha -= 3;
		
		if (BoldNumber[i]->Alpha <= 0)
		{
			delete BoldNumber[i];
			BoldNumber.erase(BoldNumber.begin() + i);		//�z��J��
			i--;											//���������߂�
		}
	}

	//9�b���狭���ƃT�E���h�Đ�
	if (displayTime_s <= 9)		//��	2���\���ł��Ȃ���肠��
	{
		if(displayTime_s == 9)GetSound.Play2D(Clock_Sound);		//�T�E���h�͈ړ�
		
		
		if (memoryTime == displayTime_s)return;		//�O��ƒl�ɕω�������������X�L�b�v����

		memoryTime = displayTime_s;

		BoldNumber.push_back(new BoldNumberData);

		//�I�[�̗v�f������
		auto Tmp = BoldNumber.back();
		Tmp->Alpha = 255;
		Tmp->DisplayNum = displayTime_s;

		D3DXMATRIX TmpScal;
		D3DXMatrixScaling(&TmpScal, 1.0f, 1.0f, 1.0f);
		Tmp->ScalMat = TmpScal;
	}
}

void TimeUI::SetTime_s(int setTime_s)
{
	displayTime_s = setTime_s;
}
