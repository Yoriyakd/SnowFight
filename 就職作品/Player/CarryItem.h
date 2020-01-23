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
	//��̃A�C�e���̕\���Ǘ�
	void SetDisplayFlag(bool _Flag);

private:
	const CarryObjectID *id;
	XFILE* nowCarryItemMesh;
	XFILE RedBallMesh, BlueBallMesh, YellowBallMesh, SnowBallMesh;
	D3DXMATRIX itemOffsetMat, itemMat;
	D3DXMATRIX ScalingMat;		//�f�R���[�V����������������s��
	const D3DXMATRIX* armRMat_p;		//�r�̍s��̃|�C���^��ۑ�

	bool displayFlag;
};