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
	D3DXMATRIX backMat, numberOffsetMat;			//numberMat‚Í”wŒi‰æ‘œ‚©‚ç‚Ì‹——£‚ğ“ü‚ê‚é
	int displayBallCnt;		//‰æ–Ê‚É•\¦‚·‚éƒ{[ƒ‹‚Ì”
};