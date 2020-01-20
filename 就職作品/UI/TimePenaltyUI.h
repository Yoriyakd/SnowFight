#pragma once
#include"../ResourceManager.h"
class TimePenaltyUI
{
public:
	TimePenaltyUI(int _MinusTime);
	~TimePenaltyUI();
	void Draw();
	bool Update();

	LPDIRECT3DTEXTURE9 minusTex;
	LPDIRECT3DTEXTURE9 numberTex;

	int displayTime_s;		//表示する時間(秒)
	int alpha = 255;
	D3DXMATRIX mat;
	D3DXMATRIX numberOffsetMat;
};