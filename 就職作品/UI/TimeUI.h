#pragma once
#include"../ResourceManager.h"
class TimeUI {
public:
	TimeUI();
	~TimeUI();
	void Draw();
	void SetTime_s(int setTime_s);		//�\�����鎞�Ԃ��Z�b�g����(�b)
private:
	int displayTime_s;		//�\�����鎞��(�b)
	LPDIRECT3DTEXTURE9 logoTex, numberTex;
	D3DXMATRIX logoMat, numberOffsetMat;
};