#pragma once
#include"../ResourceManager.h"
class RemainingBallUI {
public:
	RemainingBallUI();
	~RemainingBallUI();
	void SetRemainingBallCnt(int Cnt);
	void Draw();
private:
	LPDIRECT3DTEXTURE9 backTex, numberTex;
	D3DXMATRIX backMat, numberOffsetMat;			//numberMat�͔w�i�摜����̋���������
	int displayBallCnt;		//��ʂɕ\������{�[���̐�
};