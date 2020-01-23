#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../Item/DecorationBase.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------

class CarryItem {
public:
	CarryItem(const D3DXMATRIX *ArmRMat_p);
	~CarryItem();
	void Draw();
	void Updata();
	void SetNowCarryItemPointer(const CarryObjectID *_ID);
	//手のアイテムの表示管理
	void SetDisplayFlag(bool _Flag);

private:
	const CarryObjectID *id;
	XFILE* nowCarryItemMesh;
	XFILE RedBallMesh, BlueBallMesh, YellowBallMesh, SnowBallMesh;
	D3DXMATRIX itemOffsetMat, itemMat;
	D3DXMATRIX ScalingMat;		//デコレーションを小さくする行列
	const D3DXMATRIX* armRMat_p;		//腕の行列のポインタを保存

	bool displayFlag;
};