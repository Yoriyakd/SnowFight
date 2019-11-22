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
	D3DXMATRIX backMat, numberOffsetMat;			//numberMatは背景画像からの距離を入れる
	int displayBallCnt;		//画面に表示するボールの数
};