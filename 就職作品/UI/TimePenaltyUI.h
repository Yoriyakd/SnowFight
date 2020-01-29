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
	int effectDisplayFlag;		//点滅させるための表示非表示切り替えフラグ
	const int EFFECT_FLASH_INTERVAL = 15;	//点滅の間隔
	int flashIntervalCnt;

	int penaltyTime_s;		//減少する時間(秒)
	int displayTime_frame;	//表示時間
	int alpha = 255;
};