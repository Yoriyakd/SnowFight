#pragma once
#include"../main.h"
#include"../ResourceManager.h"
//雪玉の軌跡		デザインがひどいので用変更
class SnowLocus{
private:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	VERTEX vertex[4];
	int alpha = 255;
public:
	SnowLocus(D3DXMATRIX SnowBallMat);
	~SnowLocus();
	void SetMat(D3DXMATRIX SnowBallMat);		//雪玉の行列を渡す	いらないかも
	void Draw();
	bool Update();
};
