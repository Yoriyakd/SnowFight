#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class SnowLocus{
public:
	SnowLocus(const D3DXMATRIX &SnowBallMat);
	~SnowLocus();
	void Draw();
	bool Update();
	void SetBillBoardMat(const D3DXMATRIX &BillBoardMat);
private:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	VERTEX vertex[4];
	int alpha = 255;
	D3DXMATRIX billBoardMat;
};
