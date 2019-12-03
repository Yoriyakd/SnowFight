#include "TimeUI.h"

TimeUI::TimeUI()
{
	numberTex = resourceManager->GetTexture("Number_Time.png", 460, 50, NULL);
	D3DXMatrixTranslation(&numberOffsetMat, 10, 56, 0);

	logoTex = resourceManager->GetTexture("TimeLogo.png", 194, 46, NULL);
	D3DXMatrixTranslation(&logoMat, 0, 0, 0);
}

TimeUI::~TimeUI()
{
}

void TimeUI::Draw()
{
	RECT RcLogo = { 0, 0, 194, 46 };
	lpSprite->SetTransform(&logoMat);
	lpSprite->Draw(logoTex, &RcLogo, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


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

		lpSprite->SetTransform(&NumberMat);
		lpSprite->Draw(numberTex, &RcNumber, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		NumberMat = NumberDisMat * NumberMat;			//�E�ɂ��炷
	}
	
}

void TimeUI::SetTime_s(int setTime_s)
{
	displayTime_s = setTime_s;
}
