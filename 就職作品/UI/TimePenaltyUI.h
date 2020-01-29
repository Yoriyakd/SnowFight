#pragma once
#include"../ResourceManager.h"
class TimePenaltyUI
{
public:
	TimePenaltyUI(int _MinusTime);
	~TimePenaltyUI();
	void Draw();
	bool Update();

private:
	LPDIRECT3DTEXTURE9 minusTex;
	LPDIRECT3DTEXTURE9 numberTex;

	D3DXMATRIX mat;
	D3DXMATRIX numberOffsetMat;

	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectDisplayFlag;		//�_�ł����邽�߂̕\����\���؂�ւ��t���O
	const int EFFECT_FLASH_INTERVAL = 15;	//�_�ł̊Ԋu
	int flashIntervalCnt;

	int penaltyTime_s;		//�������鎞��(�b)
	int displayTime_frame;	//�\������
	int alpha = 255;
};