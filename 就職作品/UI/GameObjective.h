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
	D3DXMATRIX backMat, numberOffsetMat;			//numberMat�͔w�i�摜����̋���������

	int normCnt, nowCnt;
	bool normState;
};