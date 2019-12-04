#pragma once
#include"../ResourceManager.h"
class GameObjective {
public:
	GameObjective();
	~GameObjective();
	void SetNorm(int Norm);
	void SetNowNormCnt(int NowCnt);
	void SetNormState(bool NormState);
	void Draw();
private:
	LPDIRECT3DTEXTURE9 backTex, numberTex, clearTex;
	D3DXMATRIX backMat, numberOffsetMat;			//numberMat‚Í”wŒi‰æ‘œ‚©‚ç‚Ì‹——£‚ð“ü‚ê‚é

	int normCnt, nowCnt;
	bool normState;
};