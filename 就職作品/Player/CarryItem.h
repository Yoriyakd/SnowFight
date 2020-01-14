#pragma once
#include"../main.h"
#include"../ResourceManager.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------

class CarryItem {
public:
	CarryItem(const D3DXMATRIX *ArmRMat_p);
	~CarryItem();
	void Draw();
	void Updata();

	XFILE* nowCarryItem;
	XFILE RedBallMesh, BlueBallMesh, YellowBallMesh;
	D3DXMATRIX itemOffsetMat, itemMat;
	const D3DXMATRIX* armRMat_p;		//腕の行列のポインタを保存
};