#pragma once
#include"../ResourceManager.h"
class TimeUI {
public:
	TimeUI();
	~TimeUI();
	void Draw();
	void SetTime_s(int setTime_s);		//表示する時間をセットする(秒)
private:
	int displayTime_s;		//表示する時間(秒)
	LPDIRECT3DTEXTURE9 logoTex, numberTex;
	D3DXMATRIX logoMat, numberOffsetMat;
};