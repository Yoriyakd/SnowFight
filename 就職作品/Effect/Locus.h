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
	D3DXMATRIX billBoardMat;
public:
	SnowLocus(D3DXMATRIX SnowBallMat);
	~SnowLocus();
	void Draw();
	bool Update();
	void SetBillBoardMat(D3DXMATRIX BillBoardMat);
};
